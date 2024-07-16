#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_video_file>" << std::endl;
        return -1;
    }

    cv::VideoCapture cap(argv[1],NULL);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video." << std::endl;
        return -1;
    }

    cv::namedWindow("Video", cv::WINDOW_AUTOSIZE);
    cv::Mat frame;

    while (true) {
        bool ret = cap.read(frame); // Read a frame from the video
        if (!ret) {
            std::cout << "End of video" << std::endl;
            break;
        }

        cv::imshow("Video", frame); // Display the frame

        if (cv::waitKey(25) == 'q') { // Break the loop if the 'q' key is pressed
            break;
        }
    }

    cap.release(); // Release the video capture object
    cv::destroyAllWindows(); // Close all OpenCV windows

    return 0;
}
