#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

const int IMG_WIDTH  = 512;
const int IMG_HEIGHT = 400;

int main(int argc, char **argv)
{
        Mat img_gray;
        Mat hist_img = Mat(IMG_HEIGHT, IMG_WIDTH, CV_8UC1, Scalar(0));

        Mat img = imread("./Monkey.jpep");
        if(!img.data) {
                std::cout << "Error reading image" << std::endl;
                return 1;
        };

        imshow("Original", img);
        waitKey(0);
        destroyWindow("Original");

        cvtColor(img, img_gray, CV_BGR2GRAY);

        int pixel_values[256] = {0};

        std::cout << "Image channels: " << img_gray.channels() << std::endl; // Should be 1

        const int total_pixels = img_gray.rows * img_gray.cols;
        const int RATIO = 3500 / IMG_HEIGHT ;

        for(int p = 0; p < total_pixels; ++p)
        {
               uint8_t pixel = img_gray.at<uint8_t>(p);
               pixel_values[pixel]++;
        }

        /* for(int p = 0; p < 256; ++p) */
        /* { */
        /*         std::cout << "Pixel[" << p << "] = " << pixel_values[p] << std::endl; */
        /* }; */

        /* std::cout << "----------------------------------------" << std::endl; */

        /* 
         * The histogram is divided into x and y axis 
         * X axis goes from 0 to 255 
         * Y axis goes from 0 to (img.rows * img.cols) / RATIO
         */
        for(ssize_t v = 0; v < 256; ++v)
        {
                Point start(v, IMG_HEIGHT);
                Point end(v, IMG_HEIGHT - (pixel_values[v] / RATIO));
                /* std::cout << "pixel[" << v << "] = " << start.x << " " << start.y << ", " << end.x << " " << end.y << std::endl; */
                line(hist_img, start, end, Scalar(255, 255, 255));
        };

        imshow("Histogram", hist_img);
        waitKey(0);
        destroyWindow("Histogram");

        destroyAllWindows();

}
