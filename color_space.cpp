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
                        case 0: // blue
                                line(img_hist, start, end, Scalar(0, 0, 255));
                                break;
                        case 1: // green
                                line(img_hist, start, end, Scalar(0, 255, 0));
                                break;
                        case 2: // red
                                line(img_hist, start, end, Scalar(255, 0, 0));
                                break;
                        };
                };
                counter = 0; 
        };        
        imshow("Histogram", img_hist);
        waitKey(0);
        destroyWindow("Histogram");

// #if NEW_V
//         uint8_t pixels_h[256], pixels_s[256], pixels_v[256];

//         const int total_pixels = img_hsv.rows * img_hsv.cols;
//         const int RATIO = 1000 / IMG_HEIGHT;
//         const int STEP = IMG_WIDTH / 256;

//         for(int p = 0; p < total_pixels; ++p)
//         {
//                 uint8_t pixel = img_hsv_channels[0].at<uint8_t>(p);
//                 pixels_h[pixel]++;
//         }

//         for(int p = 0; p < total_pixels; ++p)
//         {
//                 uint8_t pixel = img_hsv_channels[1].at<uint8_t>(p);
//                 pixels_s[pixel]++;
//         }

//         for(int p = 0; p < total_pixels; ++p)
//         {
//                 uint8_t pixel = img_hsv_channels[2].at<uint8_t>(p);
//                 pixels_v[pixel]++;
//         }


//         ssize_t counter = 0;
//         for(ssize_t p = 0; p < 255;)
//         {
//                 Point start(counter, IMG_HEIGHT - (pixels_h[p] / RATIO));
//                 counter += STEP;
//                 p++;
//                 Point end(counter, IMG_HEIGHT - (pixels_h[p] / RATIO));
//                 line(img_hist, start, end, Scalar(0, 0, 255));
//         };
//         counter = 0;

//         for(ssize_t p = 0; p < 255;)
//         {
//                 Point start(counter, IMG_HEIGHT - (pixels_s[p] / RATIO));
//                 counter += STEP;
//                 p++;
//                 Point end(counter, IMG_HEIGHT - (pixels_s[p] / RATIO));
//                 line(img_hist, start, end, Scalar(0, 255, 0));
//         };
//         counter = 0;
        
//         for(ssize_t p = 0; p < 255;)
//         {
//                 Point start(counter, IMG_HEIGHT - (pixels_v[p] / RATIO));
//                 counter += STEP;
//                 p++;
//                 Point end(counter, IMG_HEIGHT - (pixels_v[p] / RATIO));
//                 line(img_hist, start, end, Scalar(255, 0, 0));
//         };

//         imshow("Histogram", img_hist);
//         waitKey(0);
//         destroyWindow("Histogram");
// #endif
        
        /* Mat hist; */
        /* int channels[] = {0, 1, 2}; */
        /* int dims = 3; // Only 1 channel, the hue channel */
        /* int histSize[] = {0, 30}; // 9 bins, 1 each for Red, RY, Yellow, YG etc. */
        /* float hRange[] = {0, 180}; */
        /* float sRange[] = {0, 256}; */
        /* float vRange[] = {0, 256}; */
        /* const float *ranges[] = {hRange, sRange, vRange}; */

        /* std::cout << "Displaying new histogram" << std::endl; */
        
        /* calcHist(&img_hsv, 1, channels, Mat(), hist, dims, histSize, ranges, true, false); */
        /* imshow("Histogram", hist); */
        /* waitKey(0); */
        /* destroyWindow("Histogram"); */
        
        destroyAllWindows();
        
}
