#include "global.h"
#include "opencv2/nonfree/features2d.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	if(argc < 3) {
		cout << "Please include two valid picture files in command line" << endl;
		return 1;
	}
	Mat image_1 = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	Mat image_2 = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);
	//write(image, "output.raw");

	SIFT SIFT_detector(0, 3, 0.04, 10, 1.6);
	std::vector<KeyPoint> keypoints_SIFT_1, keypoints_SIFT_2;
	SIFT_detector.detect(image_1, keypoints_SIFT_1);
	SIFT_detector.detect(image_2, keypoints_SIFT_2);

	SiftDescriptorExtractor SIFT_extractor;
	Mat descriptors1, descriptors2;
	SIFT_extractor.compute(image_1, keypoints_SIFT_1, descriptors1);
	SIFT_extractor.compute(image_2, keypoints_SIFT_2, descriptors2);

	BFMatcher matcher = BFMatcher(NORM_L2);
	vector<DMatch> matches;
	matcher.match(descriptors1, descriptors2, matches);

	matches.resize(40);

	Mat image_matches;
	drawMatches(image_1, keypoints_SIFT_1, image_2, keypoints_SIFT_2, matches, image_matches);
	imshow("SIFT matches", image_matches);
	imwrite("SIFT_matches.jpg", image_matches);


	SURF SURF_detector;
	std::vector<KeyPoint> keypoints_SURF_1, keypoints_SURF_2;
	SURF_detector.detect(image_1, keypoints_SURF_1);
	SURF_detector.detect(image_2, keypoints_SURF_2);

	SurfDescriptorExtractor SURF_extractor;
	Mat descriptors_SURF_1, descriptors_SURF_2;
	SURF_extractor.compute(image_1, keypoints_SURF_1, descriptors_SURF_1);
	SURF_extractor.compute(image_2, keypoints_SURF_2, descriptors_SURF_2);

	BFMatcher SURF_matcher = BFMatcher(NORM_L2);
	vector<DMatch> matches_SURF;
	SURF_matcher.match(descriptors_SURF_1, descriptors_SURF_2, matches_SURF);

	matches_SURF.resize(40);

	Mat image_matches_SURF;
	drawMatches(image_1, keypoints_SURF_1, image_2, keypoints_SURF_2, matches_SURF, image_matches_SURF);
	imshow("SURF matches", image_matches_SURF);
	imwrite("SURF_matches.jpg", image_matches_SURF);

	waitKey(0);

	return 0;
}