#include <iostream>
#include <math.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char **argv) {
        // Amplitude of the histogram
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
                std::cout << "Intensity[" 
                        << std::setfill('0') << std::setw(3)
                        << p << "] = " 
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

        // If we apply now the minMaxLoc function to the equalized image
        // the minimum is at 0 and the maximum at 255 because we have stretched 
        // the histogram to have all possible values
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

#endif

#if COLOR_MAP
        // Create and apply a color map to an image
        // To create a custom color_map we can create three LUTs for each 
        // channel and then apply in to the three channels, or a LUT with 
        // 3 channels

        Mat img_color_map;
        Mat img_orig_color = imread(argv[1]);
        Mat color_map = Mat(1, 256, CV_8UC3);
        Vec3b point;

        for(int m = 0; m < 256; ++m)
        {
                point.val[0] = m;
                point.val[1] = m;
                point.val[2] = 255 - m;
                color_map.at<Vec3b>(m) = point;
        };

        applyColorMap(img_orig_color, img_color_map, COLORMAP_JET);
        /* LUT(img_orig_color, color_map, img_color_map); */

        imshow("Color map applied", img_color_map);
        waitKey(0);
        destroyWindow("Color map applied");
#endif

        destroyAllWindows();
}
