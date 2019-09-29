// Program to work with multiple color spaces

#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

const int IMG_WIDTH  = 1024;
const int IMG_HEIGHT = 512;
const int CHANNELS = 3;

int main(int argc, char **argv)
{
        Mat img_gray, img_hsv, img_bgr_channels[3], img_hsv_channels[3];
        Mat img_hist = Mat(IMG_HEIGHT, IMG_WIDTH, CV_8UC3, Scalar(0));
        Mat img_orig = imread(argv[1]);
        if(!img_orig.data)
        {
                std::cout << "Error loading image." <<std::endl;
                return 1;
        };

        imshow("Original", img_orig);
        waitKey(0);
        destroyWindow("Original");
        
        std::cout << "Image channels: " << img_orig.channels() << std::endl;
        
        cvtColor(img_orig, img_gray, CV_BGR2GRAY);
        cvtColor(img_orig, img_hsv, CV_BGR2HSV);

        split(img_orig, img_bgr_channels);

#if SHOW_IMG
        imshow("Blue channel", img_bgr_channels[0]);
        waitKey(0);
        imshow("Green channel", img_bgr_channels[1]);
        waitKey(0);
        imshow("Red channel", img_bgr_channels[2]);
        waitKey(0);
#endif

        // Convert the image to HSV and calculate its histogram
        cvtColor(img_orig, img_hsv, CV_BGR2HSV);
        imshow("HSV", img_hsv);
        waitKey(0);
        destroyWindow("HSV");

        int pixel_values[3][256] = {{0}};
        
        const int total_pixels = img_hsv.rows * img_hsv.cols;
        const int RATIO = 9000 / IMG_HEIGHT;
        const int STEP = IMG_WIDTH / 256;
        
        for(int p = 0; p < total_pixels; ++p)
        {
                Vec3b pixel = img_hsv.at<Vec3b>(p);
                pixel_values[0][(uint8_t)pixel.val[0]]++; // H
                pixel_values[1][(uint8_t)pixel.val[1]]++; // S
                pixel_values[2][(uint8_t)pixel.val[2]]++; // V
                
        }

        ssize_t counter = 0;
        for(ssize_t c = 0; c < CHANNELS; ++c)
        {
                for(ssize_t p = 0; p < 255;)
                {
                        Point start(counter, IMG_HEIGHT - (pixel_values[c][p] / RATIO));
                        counter += STEP;
                        p++;
                        Point end(counter, IMG_HEIGHT - (pixel_values[c][p] / RATIO));
                        switch(c)
                        {
                        case 0: // H
                                line(img_hist, start, end, Scalar(0, 0, 255));
                                break;
                        case 1: // S
                                line(img_hist, start, end, Scalar(0, 255, 0));
                                break;
                        case 2: // V
                                line(img_hist, start, end, Scalar(255, 0, 0));
                                break;
                        };
                };
                counter = 0; 
        };        
        imshow("Histogram", img_hist);
        waitKey(0);
        destroyWindow("Histogram");
      
        destroyAllWindows();
        
}
