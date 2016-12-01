-- hw4 problem 2 part a to test negative images
require 'nn';
require "optim"

net = torch.load("../res/p1b_network.t7")

testset_c = torch.load('../res/mnist-p1b-test.t7')
testset_c.data = 255 - testset_c.data
testset_c.data = testset_c.data:double()

setmetatable(testset_c, 
    {__index = function(t, i) 
                    return {t.data[i], t.label[i]} 
                end
    }
);

function testset_c:size()
  return self.data:size(1)
end

mean_c = testset_c.data:mean() -- mean estimation
print('Channel ' .. 1 .. ', Mean: ' .. mean_c)
testset_c.data:add(-mean_c) -- mean subtraction

stdv_c = testset_c.data:std() -- std estimation
print('Channel ' .. 1 .. ', Standard Deviation: ' .. stdv_c)
testset_c.data:div(stdv_c) -- std scaling

--mean average precision
map = {}
for i=1,10 do
  -- first value is for sum of precisions.
  -- second value is for total number of labels
  -- third value for total number of correct labels
  map[i] = {0,0,0}
end

classes = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
confusion_test = optim.ConfusionMatrix(classes)
for i=1,10000 do
    local groundtruth = testset_c.label[i]
    local prediction = net:forward(testset_c.data[i])
    local confidences, indices = torch.sort(prediction, true)  -- true means sort in descending order
    map[groundtruth][2] = map[groundtruth][2] + 1
    if groundtruth == indices[1] then
        map[groundtruth][3] = map[groundtruth][3] + 1
        map[groundtruth][1] = map[groundtruth][1] + map[groundtruth][3]/map[groundtruth][2]
    end
    confusion_test:add(prediction, groundtruth)
    confusion_test:updateValids()
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