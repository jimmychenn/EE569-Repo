require 'nn';
require "optim"

trainset = torch.load('../res/mnist-p1b-train.t7')
testset = torch.load('../res/mnist-p1b-test.t7')
trainset.data = trainset.data:double() -- convert the data from a ByteTensor to a DoubleTensor.
testset.data = testset.data:double()


print(trainset)
print(#trainset.data)
print(testset)
print(#testset.data)

setmetatable(trainset, 
    {__index = function(t, i) 
                    return {t.data[i], t.label[i]} 
                end
    }
);

mean = trainset.data:mean() -- mean estimation
print('Channel ' .. 1 .. ', Mean: ' .. mean)
trainset.data:add(-mean) -- mean subtraction

stdv = trainset.data:std() -- std estimation
print('Channel ' .. 1 .. ', Standard Deviation: ' .. stdv)
trainset.data:div(stdv) -- std scaling

function trainset:size() 
    return self.data:size(1) 
end



testset_c = testset
testset_c.data = 255 - testset_c.data
trainset_c = trainset
trainset_c.data = 255 - trainset_c.data
setmetatable(trainset_c, 
    {__index = function(t, i) 
                    return {t.data[i], t.label[i]} 
                end
    }
);

function trainset_c:size()
	return self.data:size(1)
end

mean_c = trainset_c.data:mean() -- mean estimation
print('Channel ' .. 1 .. ', Mean: ' .. mean_c)
trainset.data:add(-mean_c) -- mean subtraction

stdv_c = trainset_c.data:std() -- std estimation
print('Channel ' .. 1 .. ', Standard Deviation: ' .. stdv_c)
trainset_c.data:div(stdv_c) -- std scaling


-- exact same network as in 4b but use training data of both original and negative images

net = nn.Sequential()
net:add(nn.SpatialConvolution(1, 6, 5, 5))
net:add(nn.ReLU())
net:add(nn.SpatialMaxPooling(2,2,2,2))
net:add(nn.SpatialConvolution(6, 16, 5, 5))
net:add(nn.ReLU())
net:add(nn.SpatialMaxPooling(2,2,2,2))
net:add(nn.View(16*5*5)) 
net:add(nn.Linear(16*5*5, 120))
net:add(nn.ReLU())
net:add(nn.Linear(120, 84))
net:add(nn.ReLU())
net:add(nn.Linear(84, 10))
net:add(nn.LogSoftMax())

criterion = nn.ClassNLLCriterion()

parameters,gradParameters = net:getParameters()

print('Training...')
local nEpoch = 12
for e = 1,nEpoch do
  -- Number of training samples.
  local size  = trainset.data:size()[1]
  -- Batch size. We use a batch of samples to "smooth" the gradients.
  local bsize = 256
  -- Total loss.
  local tloss = 0

  -- Confusion matrix. This is a helpful tool.
  classes = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
  local confusion_train = optim.ConfusionMatrix(classes)
  
  for i = 1,2 do
	for t  = 1, size,bsize do
      local bsize = math.min(bsize,size-t+1)
      if i == 1 then
        input  = trainset.data:narrow(1,t,bsize)
        target = trainset.label:narrow(1,t,bsize)
      end
      if i == 2 then
      	input  = trainset_c.data:narrow(1,t,bsize)
        target = trainset_c.label:narrow(1,t,bsize)
      end
      -- Reset the gradients to zero.
      gradParameters:zero()
      -- Forward the data and compute the loss.
      local output = net:forward(input)
      local loss   = criterion:forward(output,target)
      -- Collect Statistics
      tloss = tloss + loss * bsize
      confusion_train:batchAdd(output,target)
      -- Backward. The gradient wrt the parameters are internally computed.
      local gradOutput = criterion:backward(output,target)
      local gradInput  = net:backward(input,gradOutput)
      -- The optim module accepts a function for evaluation.
      -- For simplicity I made the computation outside, and
      -- this function is used only to return the result.
      local function feval()
        return loss,gradParameters
      end
      -- Specify the training parameters.
      local config = {
        learningRate = 0.06,
      }
      -- We use the SGD method.
      optim.sgd(feval, parameters, config)
      -- Show the progress.
      io.write(string.format("progress: %4d/%4d\r",t,size))
      io.flush()
    end
  end
  -- Compute the average loss.
  tloss = tloss / size
  -- Update the confusion matrix.
  confusion_train:updateValids()
  -- Let us print the loss and the accuracy.
  -- You should see the loss decreases and the accuracy increases as the training progresses.
  print(string.format('epoch = %2d/%2d  loss = %.2f accuracy = %.2f',e,nEpoch,tloss,100*confusion_train.totalValid))
  -- You can print the confusion matrix if you want.
  --print(confusion)


  print('Testing...')
  local confusion_test = optim.ConfusionMatrix(classes)
  test_size = testset.data:size()[1]
  for j=1,2 do
    for i=1,test_size do
      if j == 1 then
        groundtruth = testset.label[i]
        prediction = net:forward(testset.data[i])
      end
      if j == 2 then
        groundtruth = testset_c.label[i]
        prediction = net:forward(testset_c.data[i])
      end
      confusion_test:add(prediction, groundtruth)
      confusion_test:updateValids()
      io.write(string.format("progress: %4d/%4d\r",i,test_size))
    end
  end
  print(string.format('test accuracy = %.2f', confusion_test.totalValid*100))

end

--mean average precision
map = {}
for i=1,10 do
  -- first value is for sum of precisions.
  -- second value is for total number of labels
  -- third value for total number of correct labels
  map[i] = {0,0,0}
end

confusion_test = optim.ConfusionMatrix(classes)
for j=1,2 do
  for i=1,10000 do
    if j == 1 then
      groundtruth = testset.label[i]
      prediction = net:forward(testset.data[i])
    end
    if j == 2 then
      groundtruth = testset_c.label[i]
      prediction = net:forward(testset_c.data[i])
    end
    local confidences, indices = torch.sort(prediction, true)  -- true means sort in descending order
    map[groundtruth][2] = map[groundtruth][2] + 1
    if groundtruth == indices[1] then
        map[groundtruth][3] = map[groundtruth][3] + 1
        map[groundtruth][1] = map[groundtruth][1] + map[groundtruth][3]/map[groundtruth][2]
    end
    confusion_test:add(prediction, groundtruth)
    confusion_test:updateValids()
  end
end

print(map)
mean_average_precision = 0
for i=1,10 do
  if map[i][3] ~= 0 then
    map[i][1] = map[i][1]/map[i][3]
  end
  mean_average_precision = mean_average_precision + map[i][1]
end
mean_average_precision = mean_average_precision/10
print(mean_average_precision)
print(string.format('test accuracy = %.2f', confusion_test.totalValid*100) .. '%')
print("Mean average precision: " .. mean_average_precision)