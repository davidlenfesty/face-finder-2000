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

/** @brief Loads images from the filesystem and trains FLANN matcher against them.
 *
 * @param fileString String that describes the location of the file.
 * @param keypoints_list List of sets of keypoints that is appended to
 * @param descriptors_list List of sets of descriptors that is appended to
 */
void load_and_train_image(String& file_string, vector<Mat>* images_list,
        vector< vector<KeyPoint> >* keypoints_list, vector<Mat>* descriptors_list);

/** @brief Prints usage for the program.
 */
void print_usage(void);

int main(int argc, char** argv) {
    // Initialise SURF feature detector
    detector = SURF::create(); // TODO: tweak parameters
    // Initialise FLANN based feature matcher.
    matcher = FlannBasedMatcher::create();

    vector<Mat> images_list;
    vector< vector<KeyPoint> > keypoints_list;
    vector<Mat> descriptors_list;

    Mat query_image;

    // Read in images
    if (argc > 2) { // if there are input arguments
        for (int i = 2; i < argc; i++) {
            String arg = String(argv[i]);
            load_and_train_image(arg, &images_list, &keypoints_list, &descriptors_list);
        }

        // Read in query image
        query_image = imread(String(argv[1]), IMREAD_COLOR);
    } else if (argc == 2) {
        printf("No training files selected!\n\r");
        print_usage();
        return -1;
    } else {
        printf("No files selected!\n\r");
        print_usage();
        return -1;
    }

    printf("Loaded Images.\n\r");

    // Compute keypoints and descriptors for query image
    vector<KeyPoint> query_keypoints;
    Mat query_descriptors;
    detector->detectAndCompute(query_image, Mat(), query_keypoints, query_descriptors);
    printf("Found descriptors.\n\r");

    // Match descriptors within a certain distance.
    // "Distance" being a term for similarity I think
    // TODO: tweak radius
    vector< vector<DMatch> > matches;
    matcher->train();
    matcher->radiusMatch(query_descriptors, matches, 0.1);

    // Sort matches into list of matches for each input image
    vector< vector<DMatch> > sorted_matches;
    for (long unsigned int i = 0; i < matches.capacity(); i++) {
        vector<DMatch> img_matches;
        sorted_matches.push_back(img_matches);
    }
    printf("Initialized sorted_matches.\n\r");

    printf("Matches size: %lu", matches.size());
    for (long unsigned int i = 0; i < matches.size(); i++) {
        for (long unsigned int j = 0; j < matches[i].size(); j++) {
            sorted_matches[ matches[i][j].imgIdx ].push_back(matches[i][j]);
        }
    }
    printf("Sorted matches! Number of images: %lu\n\r", sorted_matches.size());

    // Draw matches from query image to training image
    /*
    for (long unsigned int i = 0; i < images_list.size(); i++) {
        Mat out_image;
        drawMatches(query_image, query_keypoints, images_list[i], keypoints_list[i],
                sorted_matches[i], out_image, Scalar::all(-1), Scalar::all(-1),
                vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

        char* buf;
        sprintf(buf, "Train image %lu", i);
        String desc = String(buf);
        imshow(desc, out_image);

    }
    */
    Mat out_image;

    drawMatches(query_image, query_keypoints, images_list[0], keypoints_list[0],
            sorted_matches[0], out_image, Scalar::all(-1), Scalar::all(-1),
            vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    imshow("Thing", out_image);
    printf("Finished showing matches\n\r");
    waitKey(0);

    return 0;
}

void load_and_train_image(String& file_string, vector<Mat>* images_list,
    vector< vector<KeyPoint> >* keypoints_list, vector<Mat>* descriptors_list) {
    // Load image
    Mat train_image = imread(file_string, IMREAD_COLOR);
    images_list->push_back(train_image);

    // Detect keypoints/descriptors
    vector<KeyPoint> keypoints;
    Mat descriptors;
    detector->detectAndCompute(train_image, Mat(), keypoints, descriptors);

    // Not sure if I need these lists, just keeping them here for now
    keypoints_list->push_back(keypoints);
    descriptors_list->push_back(descriptors);

    matcher->add(descriptors);
}

void print_usage(void) {
    printf("Usage: find_face INPUT_FILE TRAINING_FILE1 [TRAININGFILE2 [...]]\n\r");
}
