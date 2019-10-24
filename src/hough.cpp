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

        imshow("Original", img_orig);
        waitKey(0);
        destroyWindow("Original");

        Mat detected_edges, img_blurred;
        int kernel_size = 3;
        int const lowThreshold = 50;
        int ratio = 2;

        GaussianBlur(img_orig, img_blurred, Size(5, 5), 1.5);
        
        Canny(img_blurred, detected_edges,lowThreshold, lowThreshold*ratio, kernel_size);

        imshow("Canny", detected_edges);
        waitKey(0);
        destroyWindow("Canny");

        Mat final_image = detected_edges;
        std::vector<Vec4i> lines;
        HoughLinesP(detected_edges, lines, 1, CV_PI/180, 100, 50, 50);
        
        cvtColor(final_image, final_image, CV_GRAY2BGR);

        for(int i = 0; i < (int)lines.size(); ++i) {
                Vec4i l = lines[i];
                line(final_image, Point(l[0], l[1]), Point(l[2], l[3]),
                     Scalar(0, 0, 255), 3, CV_AA);
        }


        imshow("Lines", final_image);
        waitKey(0);
        destroyWindow("Lines");
}
