#include <opencv2/opencv.hpp>
#include <iostream>
#include <memory.h>
#include "Camera/Frame.hpp"

Frame::Frame()
    : data(nullptr), width(0), height(0)
{

}

Frame::Frame(unsigned char* data, int width, int height, int channels)
    : width(width), height(height), channels(channels)
{
    this->data = new unsigned char[width * height * channels];
    memcpy(this->data, data, width * height * channels * sizeof(unsigned char));
}

Frame::Frame(const Frame& frame)
    : width(frame.width), height(frame.height), channels(frame.channels)
{
    data = new unsigned char[width * height * channels];
    memcpy(data, frame.data, width * height * channels * sizeof(unsigned char));
}

Frame::~Frame()
{
    if (data) delete[] data;
}

const unsigned char* Frame::getData() const
{
    return data;
}

const int Frame::getWidth() const
{
    return width;
}

const int Frame::getHeight() const
{
    return height;
}

const int Frame::getChannels() const
{
    return channels;
}

unsigned char* Frame::encodeJPG(int quality, int* size) const
{
    cv::Mat img(height, width, CV_8UC3, data);
    std::vector<uchar> buffer;
    std::vector<int> params = {cv::IMWRITE_JPEG_QUALITY, quality};
    cv::imencode(".jpg", img, buffer, params);

    unsigned char* jpg = new unsigned char[buffer.size()];
    memcpy(jpg, buffer.data(), buffer.size());
    if (size) *size = buffer.size();
    return jpg;
}