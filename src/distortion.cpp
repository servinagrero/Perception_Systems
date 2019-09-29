// Program to distort an image in a variety of ways

#include <iostream>
#include <math.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

#define PI 3.14159265

using namespace cv;

int main(int argc, char **argv)
{
        Mat img_orig = imread(argv[1]);
        if (!img_orig.data) {
                std::cout << "Error loading image." << std::endl;
                return 1;
        };

        imshow("Original", img_orig);
        waitKey(0);

        // TODO: Tweak the algorith to make the distortions smoother
        Mat img_final = Mat(img_orig.rows, img_orig.cols, CV_8UC3);
        int counter = 0, angle = 0, direction = 1, distortion = 50;
        for(int r = 0; r < img_orig.rows; ++r)
        {
                for(int c = 0; c < img_orig.cols; ++c)
                {
                        img_final.at<Vec3b>(r, c) = img_orig.at<Vec3b>(r, (c + counter) % img_orig.cols);
                }
                angle += direction;
                counter = -(int)(sin(angle*PI/180) * distortion);
                distortion += 1;
                std::cout << "Angle: " << angle << ", Counter: " << counter << std::endl;
        }

        imshow("Original", img_final);
        waitKey(0);
        destroyAllWindows();
}
