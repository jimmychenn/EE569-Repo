#include "global.h"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <map>

using namespace std;

int main(int argc, char* argv[]) {
	Mat jeep = imread(P2A_IN1, CV_LOAD_IMAGE_GRAYSCALE);
	Mat bus = imread(P2A_IN2, CV_LOAD_IMAGE_GRAYSCALE);
	Mat rav4_1 = imread(P2B_IN1, CV_LOAD_IMAGE_GRAYSCALE);

	SIFT SIFT_detector;
	std::vector<KeyPoint> keypoints_jeep, keypoints_bus, keypoints_rav4;
	SIFT_detector.detect(jeep, keypoints_jeep);
	SIFT_detector.detect(bus, keypoints_bus);
	SIFT_detector.detect(rav4_1, keypoints_rav4);

	SiftDescriptorExtractor SIFT_extractor;
	Mat descriptors_jeep, descriptors_bus, descriptors_rav4;
	SIFT_extractor.compute(jeep, keypoints_jeep, descriptors_jeep);
	SIFT_extractor.compute(bus, keypoints_bus, descriptors_bus);
	SIFT_extractor.compute(rav4_1, keypoints_rav4, descriptors_rav4);

	Mat labels_jeep, labels_bus, labels_rav4;
	kmeans(descriptors_jeep, 8, labels_jeep, 
		TermCriteria(TermCriteria::EPS+TermCriteria::COUNT, 10000, 1.0),
		3, KMEANS_RANDOM_CENTERS);

	kmeans(descriptors_bus, 8, labels_bus, 
		TermCriteria(TermCriteria::EPS+TermCriteria::COUNT, 10000, 1.0),
		3, KMEANS_RANDOM_CENTERS);

	kmeans(descriptors_rav4, 8, labels_rav4, 
		TermCriteria(TermCriteria::EPS+TermCriteria::COUNT, 10000, 1.0),
		3, KMEANS_RANDOM_CENTERS);


	int hist[8][3] = {0};
	for(int i = 0; i < labels_jeep.rows; i++) {
		//cout << labels_jeep.at<int>(i) << endl;
		hist[labels_jeep.at<int>(i)][0]++;
	}
	for(int i = 0; i < labels_bus.rows; i++) {
		//cout << labels_jeep.at<int>(i) << endl;
		hist[labels_bus.at<int>(i)][1]++;
	}
	for(int i = 0; i < labels_rav4.rows; i++) {
		//cout << labels_jeep.at<int>(i) << endl;
		hist[labels_rav4.at<int>(i)][2]++;
	}

	cout << "jeep histogram" << endl;
	for(int i = 0; i < 8; i++) {
		cout << i << ":" << hist[i][0] << endl;
	}
	cout << "bus histogram" << endl;
	for(int i = 0; i < 8; i++) {
		cout << i << ":" << hist[i][1] << endl;
	}
	cout << "rav4 histogram" << endl;
	for(int i = 0; i < 8; i++) {
		cout << i << ":" << hist[i][2] << endl;
	}


	Mat rav4_2 = imread(P2B_IN2, CV_LOAD_IMAGE_GRAYSCALE);
	std::vector<KeyPoint> keypoints_rav4_2;
	SIFT_detector.detect(rav4_2, keypoints_rav4_2);
	Mat descriptors_rav4_2;
	SIFT_extractor.compute(rav4_2, keypoints_rav4_2, descriptors_rav4_2);
	Mat labels_rav4_2;
	kmeans(descriptors_rav4_2, 8, labels_rav4_2,
		TermCriteria(TermCriteria::EPS+TermCriteria::COUNT, 10000, 1.0),
		3, KMEANS_RANDOM_CENTERS);

	int hist_test[8] = {0};

	for(int i = 0; i < labels_rav4_2.rows; i++) {
		//cout << labels_jeep.at<int>(i) << endl;
		hist_test[labels_rav4_2.at<int>(i)]++;
	}
	cout << "rav4_2 test histogram" << endl;
	for(int i = 0; i < 8; i++) {
		cout << i << ":" << hist_test[i] << endl;
	}

	int l2_dist[3] = {0};

	for(int j = 0; j < 3; j++) {
		int dist = 0;
		for(int i = 0; i < 8; i++) {
			dist += pow(hist_test[i] - hist[i][j], 2);
		}
		l2_dist[j] = pow(dist, 0.5);
	}
	
	for(int i = 0; i < 3; i++) {
		cout << "L2 Distance: " << l2_dist[i] << endl;
	}

	return 0;
}