// Program to obtain and draw the histogram of an image

#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

const int IMG_WIDTH  = 300;
const int IMG_HEIGHT = 400;

int main(int argc, char **argv)
{
        Mat img_gray;
        Mat hist_img = Mat(IMG_HEIGHT, IMG_WIDTH, CV_8UC1, Scalar(0));

        Mat img = imread(argv[1]);
        if(!img.data) {
                std::cout << "Error reading image" << std::endl;
                return 1;
        };

        imshow("Original", img);
        waitKey(0);
        destroyWindow("Original");

        cvtColor(img, img_gray, CV_BGR2GRAY);

        int pixel_values[256] = {0};

        // Should be 1 for a gray image and 3 for color images
        std::cout << "Image channels: " << img_gray.channels() << std::endl;

        const int total_pixels = img_gray.rows * img_gray.cols;
        const int RATIO = 3500 / IMG_HEIGHT ;

        for(int p = 0; p < total_pixels; ++p)
        {
               uint8_t pixel = img_gray.at<uint8_t>(p);
               pixel_values[pixel]++;
        }
        
        // The histogram is divided into x and y axis
        // X axis goes from 0 to 255 representing the intensity of the pixel
        // Y axis represents the number of pixels with X intensity
        // In our case, it goes from 0 to (img.rows * img.cols) / RATIO
        // to prevent it from drawing outside the window
        //
        // This histogram is a bar histogram and does not take into account the
        // canvas width, as happens with color_histogram.cpp
        for(ssize_t v = 0; v < 256; ++v)
        {
                Point start(v, IMG_HEIGHT);
                Point end(v, IMG_HEIGHT - (pixel_values[v] / RATIO));
                line(hist_img, start, end, Scalar(255, 255, 255));
        };
        
        imshow("Histogram", hist_img);
        waitKey(0);
        destroyWindow("Histogram");

        destroyAllWindows();

}
