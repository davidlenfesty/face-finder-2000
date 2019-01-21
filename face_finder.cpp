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
    Mat train_image = imread("/home/isthatme/face-finder-2000/face_train.jpg", IMREAD_COLOR);
    Mat query_image = imread("/home/isthatme/face-finder-2000/face_query.jpg", IMREAD_COLOR);

    vector<KeyPoint> train_keypoints, query_keypoints;
    Mat train_descriptors, query_descriptors;

    // Compute keypoints and descriptors
    detector->detectAndCompute(train_image, Mat(), train_keypoints, train_descriptors);
    detector->detectAndCompute(query_image, Mat(), query_keypoints, query_descriptors);

    vector< vector<DMatch> > matches;
    // Match descriptors within a certain distance.
    // "Distance" being a term for similarity I think
    matcher->knnMatch(query_descriptors, train_descriptors, matches, 2); // TODO: tweak radius

    // Find "good" matches. Just doing this for now to reduce to a 1d matrix
    vector<DMatch> good_matches;
    for (int i = 0; i < static_cast<int>(matches.size()); i++) {
        if (matches[i][0].distance < matches[i][1].distance * 0.7) {
            good_matches.push_back(matches[i][0]);
        }
    }

    Mat out_image;
    // Draw matches from query image to training image
    drawMatches(query_image, query_keypoints, train_image, train_keypoints,
            good_matches, out_image, Scalar::all(-1), Scalar::all(-1),
            vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    imshow("Face detection", out_image);
    waitKey(0);

    return 0;
}
