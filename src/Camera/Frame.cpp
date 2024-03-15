#include <iostream>
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
    if (data != nullptr)
        delete[] data;
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
