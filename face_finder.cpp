#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;


// Pointers for feature detection and matching objects.
Ptr<SURF> detector;
Ptr<FlannBasedMatcher> matcher;

// Helper functions
void load_and_train_image(char* fileString);

int main(int argc, char** argv) {
    // Initialise SURF feature detector
    detector = SURF::create(); // TODO: tweak parameters
    // Initialise FLANN based feature matcher.
    matcher = FlannBasedMatcher::create();

    // Read in images
    Mat train_image = imread("/home/isthatme/face_train.png", CV_LOAD_IMAGE_COLOR);
    Mat query_image = imread("/home/isthatme/face_query.png", CV_LOAD_IMAGE_COLOR);

    vector<KeyPoint> train_keypoints, query_keypoints;
    Mat train_descriptors, query_descriptors;

    // Compute keypoints and descriptors
    detector->detectAndCompute(train_image, Mat(), train_keypoints, train_descriptors);
    detector->detectAndCompute(query_image, Mat(), query_keypoints, query_descriptors);

    vector< vector<DMatch> > matches;
    // Match descriptors within a certain distance.
    // "Distance" being a term for similarity I think
    matcher->radiusMatch(query_descriptors, train_descriptors, matches, 5); // TODO: tweak radius

    Mat out_image;
    // Draw matches from query image to training image
    drawMatches(query_image, query_keypoints, train_image, train_keypoints,
            matches[0], out_image, Scalar::all(-1), Scalar::all(-1),
            vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    imshow("Face detection", out_image);
    waitKey(0);

    return 0;
}
