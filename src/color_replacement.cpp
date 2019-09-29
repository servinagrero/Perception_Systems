// Program to apply color replacement to an image

#include <iostream>
#include <unistd.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

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

        Vec3b pink_px = Vec3b(203, 192, 255);

        for (int r = 0; r < img_orig.rows; ++r)
        {
                for (int c = 0; c < img_orig.cols; ++c)
                {
                        Vec3b symbol = img_orig.at<Vec3b>(r, c);

                        // This should be changed to a range of colors like GIMP does
                        // http://infofreund.de/gimp-replace-color/
                        if((int)symbol.val[2] > 200)
                                img_orig.at<Vec3b>(r, c) = pink_px;
                }
        }

        imshow("Original", img_orig);
        waitKey(0);

        destroyAllWindows();
}

