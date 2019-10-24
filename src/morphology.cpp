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

        Mat img_dilated;
        int erosion_size = 3;
        Mat kernel = getStructuringElement(MORPH_RECT,
                Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                Point( erosion_size, erosion_size ) );
        
        dilate(img_orig, img_dilated, kernel);
        
        imshow("Dilated", img_dilated);
        waitKey(0);
        destroyWindow("Dilated");


        Mat img_eroded;
        erosion_size = 7;
        kernel = getStructuringElement(MORPH_RECT,
                Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                Point( erosion_size, erosion_size ) );
        erode(img_dilated, img_eroded, kernel);
        
        imshow("Eroded", img_eroded);
        waitKey(0);
        destroyWindow("Eroded");

}
