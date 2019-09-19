#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

const int IMG_WIDTH  = 1024;
const int IMG_HEIGHT = 512;
const char CHANNELS = 3;

int main(int argc, char **argv)
{
        Mat hist_img = Mat(IMG_HEIGHT, IMG_WIDTH, CV_8UC3, Scalar(0));
        Mat img = imread(argv[1]);
        if(!img.data)
        {
                std::cout << "Error loading image." <<std::endl;
                return 1;
        };

        imshow("Original", img);
        waitKey(0);
        destroyWindow("Original");
        
        int pixel_values[CHANNELS][256] = {{0}}; // 256 values for each color
        std::cout << "Image channels: " << img.channels() << std::endl;

        const int total_pixels = img.rows * img.cols;
        const int RATIO = 3000 / IMG_HEIGHT;
        const int STEP = IMG_WIDTH / 256;
        
        for(int p = 0; p < total_pixels; ++p)
        {
                Vec3b pixel = img.at<Vec3b>(p);
                pixel_values[0][(uint8_t)pixel.val[0]]++; // blue
                pixel_values[1][(uint8_t)pixel.val[1]]++; // green
                pixel_values[2][(uint8_t)pixel.val[2]]++; // red
                
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
                        case 0: // blue
                                line(hist_img, start, end, Scalar(0, 0, 255));
                                break;
                        case 1: // green
                                line(hist_img, start, end, Scalar(0, 255, 0));
                                break;
                        case 2: // red
                                line(hist_img, start, end, Scalar(255, 0, 0));
                                break;
                        };
                };
                counter = 0; 
        };
        
        imshow("Histogram", hist_img);
        waitKey(0);
        destroyWindow("Histogram");

        destroyAllWindows();

}
