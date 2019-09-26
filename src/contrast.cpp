#include <iostream>
#include <math.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char **argv) {

        // Amplitud del histograma de una imagen
        Mat img_orig = imread(argv[1], IMREAD_GRAYSCALE);
        if (!img_orig.data) {
                std::cout << "Error loading image." << std::endl;
                return 1;
        };

        imshow("Original", img_orig);
        waitKey(0);
        destroyWindow("Original");

#if CALC_HIST
        int total_pixels = img_orig.cols * img_orig.rows;
        int pixel_values[256] = {0};
        for (int p = 0; p < total_pixels; ++p) 
        {
                uint8_t pixel = img_orig.at<uint8_t>(p);
                pixel_values[pixel]++;
        }

        for (int p = 0; p < 256; ++p) 
        {
                std::cout << "Intensity[" << p << "] = " 
                        << pixel_values[p] << std::endl;
        }

        // Find local maximum and minimum
        double min_val, max_val;
        Point min_loc, max_loc;
        minMaxLoc(img_orig, &min_val, &max_val, &min_loc, &max_loc);
        std::cout << "Min val " << min_val << " at pos " << min_loc
                    << ", max val: " << max_val << " at pos " << max_loc << std::endl;

#endif

#if EQUALIZE_HIST
        Mat hist_eq, img_result;
        equalizeHist(img_orig, hist_eq);

        imshow("Equalized histogram", hist_eq);
        waitKey(0);
        destroyWindow("Equalized histogram");

        Mat lut = Mat(1, 256, CV_8UC1);
        if(argc < 3 )
        {
                std::cout << "Lut selector must be supplied." << std::endl;
                return 1;
        }

        for(int m = 0; m < 256; ++m)
        {
                switch(*argv[2]) {
                case '1':
                lut.at<uint8_t>(m) = 255 - m;
                break;

                case '2':
                lut.at<uint8_t>(m) = 255 * (log(1 + m)/log(1 + 255));
                break;

                case '3':
                lut.at<uint8_t>(m) = m^3 / 255^2;
                break;

                default:
                lut.at<uint8_t>(m) = m;
                break;
                };
        }

        LUT(hist_eq, lut, img_result);

        imshow("LUT applied", img_result);
        waitKey(0);
        destroyWindow("LUT applied");
        destroyAllWindows();
#endif
}
