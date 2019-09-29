// Program to apply cellshading to images
//
// In order to applly cellshading to an image we need two things:
// 1) Posterize it to make it cartonish
// 2) Apply border detection
// 3) Use the border detection image as a mask to draw borders
// 4) Voila?

#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>

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

}
