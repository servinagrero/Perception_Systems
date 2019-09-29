// Program to read a black and white image and convert it to ascii
//
// Create ascii video rendering from the webcam using buffers

#include <fstream>
#include <iostream>
#include <unistd.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char **argv) 
{

#if CREATE_IMG
        Mat img_orig = imread(argv[1], IMREAD_GRAYSCALE);
        if (!img_orig.data) {
                std::cout << "Error loading image." << std::endl;
                return 1;
        };

        imshow("Original", img_orig);
        waitKey(0);
        destroyWindow("Original");

        Mat img_bw;
        resize((img_orig > 128), img_bw, cv::Size(), 0.20, 0.20);

        imshow("Black and white", img_bw);
        waitKey(0);
        destroyWindow("Black and white");

        std::ofstream text_file;
        text_file.open("ascii.txt");

        std::cout << "File created" << std::endl;

        for (int r = 0; r < img_bw.rows; ++r)
        {
                for (int c = 0; c < img_bw.cols; ++c) {
                uint8_t symbol = img_bw.at<uint8_t>(r, c);
                switch (symbol) {
                case 0:
                        text_file << " ";
                        break;
                case 255:
                        text_file << "o";
                        break;
                default:
                        text_file << "+";
                        break;
                }
                }
        text_file << "\n";
        }
        text_file.close();

#endif

        VideoCapture stream1 = VideoCapture(0);

        if (!stream1.isOpened()) {
                std::cout << "Cannot open camera" << std::endl;
                return 1;
        }

        double dWidth = stream1.get(CV_CAP_PROP_FRAME_WIDTH);
        double dHeight = stream1.get(CV_CAP_PROP_FRAME_HEIGHT);

        Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));
        std::string file_name = "Grabacion.avi";

        const float SCALE = 0.6;
        Mat cameraFrame, frame_gray, frame_bw, frame_gray_res;
        int threshold = 128, threshold_up = 120, threshold_dn = 60;
        char s_black = '&', s_gray = 'o', s_ws = ' ';
        char selector = 0;

        // TODO: Fix flickering issue when drawing text on the screen
        while (true) 
        {
                stream1.read(cameraFrame);

                if (!stream1.read(cameraFrame)) {
                        std::cout << "Failed to read frame" << std::endl;
                        return 1;
                }

                cvtColor(cameraFrame, frame_gray, CV_BGR2GRAY);
                resize((frame_gray > threshold), frame_bw, cv::Size(), SCALE, SCALE);
                resize(frame_gray, frame_gray_res, cv::Size(), SCALE, SCALE);

                imshow("Frame", frame_gray);

                system("clear");
                for (int r = 0; r < frame_bw.rows; ++r)
                {
                        for (int c = 0; c < frame_bw.cols; ++c) 
                        {
                                // TODO: Refactor this into two functions
                                if (selector == 0) // Black and white
                                {
                                        uint8_t symbol = frame_bw.at<uint8_t>(r, c);
                                        switch (symbol) {
                                        case 0:
                                                std::cout << s_black;
                                                break;
                                        case 255:
                                                std::cout << s_ws;
                                                break;
                                        default:
                                                std::cout << s_ws;
                                                break;
                                        }

                                } else { // Gray scale

                                        uint8_t symbol = frame_gray_res.at<uint8_t>(r, c);
                                        if (symbol <= threshold_dn) {
                                                std::cout << s_black;
                                        }
                                                else if (symbol >= threshold_up) {
                                                std::cout << s_ws;
                                        }
                                        else if (symbol > threshold_dn && symbol < threshold_up) {
                                                std::cout << s_gray;
                                        }
                                        else {
                                                std::cout << '+';
                                        }
                                } // End selector if
                        }
                        std::cout << "\n";
                }

                
                switch(waitKey(10)) {
                        case 27: // Escape
                                stream1.release();
                                destroyAllWindows();
                                break;
                        case 117: // u
                                threshold = threshold >= 255 ? 255 : threshold + 10;
                                threshold_up = threshold_up >= 255 ? 255 : threshold_up + 10;
                                break;
                        case 85: // U
                                threshold_dn = threshold_dn >= 255 ? 255 : threshold_dn + 10;
                                break;
                        case 68: // U
                                threshold_up = threshold_up <= 0 ? 0 : threshold_up - 10;
                                break;
                        case 100: // d
                                threshold = threshold <= 0 ? 0 : threshold - 10;
                                threshold_dn = threshold_dn <= 0 ? 0 : threshold_dn - 10;
                                break;
                        case 105: // i
                                char temp;
                                temp = s_black;
                                s_black = s_ws;
                                s_ws = temp;
                                break;
                        case 98: // b
                                selector = !selector;
                }
          }
        destroyAllWindows();
}
