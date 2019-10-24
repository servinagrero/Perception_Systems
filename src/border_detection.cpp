// Program to detect borders using the Canny algorithm

#include <iostream>

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
        destroyWindow("Original");

        // Mat histogram(256, 1, CV_32FC1);
        Mat normalized_hist;
        
        double histogram[256] = {0};
        double histogram_orig[256] = {0};
        int max1 = 0, max2 = 0, min = 0;

        // Calculamos histograma
        for(int p = 0; p < (img_orig.cols * img_orig.rows); ++p) {
                histogram[img_orig.at<uint8_t>(p)]++;
        }

        memcpy(histogram_orig, histogram, 256 * sizeof(double));

        
        // for(int i = 0; i < 256; ++i )
                // std::cout << "histogram[" << i << "] " << histogram[i] << std::endl;
        
        // Calculamos maximo 1
        for(int i = 0; i < 256; ++i) {
                if(histogram[max1] < histogram[i]) {
                        max1 = i;
                }
        }

        // Recalculamos histograma
        for(int i = 0; i < 256 ; ++i) {
                histogram[i] = histogram[i] * abs(i - max1);
        }

        // for(int i = 0; i < 256; ++i )
                // std::cout << "histogram[" << i << "] " << histogram[i] << std::endl;
        
        // Calculamos maximo 2
        for(int i = 0; i < 256; ++i) {
                if(histogram[max2] < histogram[i]) {
                        max2 = i;
                }
        }

        std::cout << "Max1: " << max1 << ", Max2: " << max2;

        if (max1 < max2) {
                
                min = max1 + 1;
                for(ssize_t c = min; c < max2; ++c) {
                        if(histogram_orig[c] < histogram_orig[min])
                                min = c;
                }
                
        } else {
                
                min = max2 + 1;
                for(ssize_t c = min; c < max1; ++c) {
                        if(histogram_orig[c] < histogram_orig[min])
                                min = c;
                }
        }

        std::cout << ", Min: " << min << std::endl;

        Mat img_bw;
        threshold(img_orig, img_bw, min, 255, THRESH_BINARY);

        imshow("BW", img_bw);
        waitKey(0);
        destroyWindow("BW");
}
