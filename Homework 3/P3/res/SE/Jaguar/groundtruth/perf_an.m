G = {};
G.groundTruth{1,1}.Boundaries = imread('Jaguar_gt1.png');
G.groundTruth{1,2}.Boundaries = imread('Jaguar_gt2.png');
G.groundTruth{1,3}.Boundaries = imread('Jaguar_gt3.png');
G.groundTruth{1,4}.Boundaries = imread('Jaguar_gt4.png');
G.groundTruth{1,5}.Boundaries = imread('Jaguar_gt5.png');
save('G_Jaguar.mat', '-struct', 'G');
[thrs, cntR, sumR, cntP, sumP, V] = edgesEvalImg(E, 'G_Jaguar.mat', 'out', 'perf_an');