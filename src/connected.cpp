// Program to detect borders using the Canny algorithm

#include <iostream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char **argv) 
{
        Mat img_orig = imread(argv[1], IMREAD_GRAYSCALE);
        
        if (!img_orig.data) {
                std::cout << "Error loading image." << std::endl;
                return 1;
        };

        cvNamedWindow( "Original", CV_WINDOW_AUTOSIZE );
        imshow("Original", img_orig);
        waitKey(0);
        // destroyWindow("Original");

        Mat img_dilated;
        int erosion_size = 3;
        Mat kernel = getStructuringElement(MORPH_RECT,
                Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                Point( erosion_size, erosion_size ) );
        
        dilate(img_orig, img_dilated, kernel);

        Mat img_detected;
        Mat labels;
        Mat stats;
        Mat centroids;
                
        connectedComponentsWithStats(img_orig, labels, stats, centroids);

        std::cout << labels.size() << " " << stats.size() << " " << centroids.size() << std::endl;
        RNG rng;

        cvtColor(img_orig, img_orig, CV_GRAY2BGR);

        std::cout << img_orig.cols << " " << img_orig.rows << std::endl;

        // The first figure is the background
        for(int i = 1; i < centroids.rows; ++i) {
                Point c_p(centroids.at<double>(i, 0), centroids.at<double>(i, 1));
                std::cout << c_p << std::endl;
                
                Point v_p1(stats.at<int>(i, CC_STAT_LEFT), stats.at<int>(i, CC_STAT_TOP));
                
                Point v_p2(stats.at<int>(i, CC_STAT_LEFT) + stats.at<int>(i, CC_STAT_WIDTH),
                        stats.at<int>(i, CC_STAT_TOP) + stats.at<int>(i, CC_STAT_HEIGHT));
                
                circle(img_orig, c_p, 3, Scalar(0, 0, 255), -1);
                rectangle(img_orig, v_p1, v_p2, Scalar(0, 255, 0));
        }
        imshow("Labeled", img_orig);
        waitKey(0);
        destroyWindow("Labeled");

}
