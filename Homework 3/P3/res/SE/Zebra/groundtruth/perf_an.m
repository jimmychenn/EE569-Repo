G = {};
G.groundTruth{1,1}.Boundaries = imread('Zebra_gt1.png');
% G.groundTruth{1,2}.Boundaries = imread('Zebra_gt2.png');
% G.groundTruth{1,3}.Boundaries = imread('Zebra_gt3.png');
% G.groundTruth{1,4}.Boundaries = imread('Zebra_gt4.png');
% G.groundTruth{1,5}.Boundaries = imread('Zebra_gt5.png');
save('G_zebra.mat', '-struct', 'G');
[thrs, cntR, sumR, cntP, sumP, V] = edgesEvalImg(E, 'G_zebra.mat', 'out', 'perf_an');