#pragma once
#include <opencv2/opencv.hpp>
#include "Camera/Frame.hpp"

void displayFrame(const Frame& f)
{
    cv::Mat frame(f.getHeight(), f.getWidth(), CV_8UC3);
    memcpy(frame.data, f.getData(), f.getWidth() * f.getHeight() * f.getChannels() * sizeof(unsigned char));

    cv::imshow("Frame", frame);
    cv::waitKey(1);
}
