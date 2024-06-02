#include <iostream>
#include <memory.h>
#include "Camera/Frame.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

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
    unsigned char* jpg = nullptr;
    *size = 0;
    if (channels == 3) // TODO : Add support for RGBA (cast to 3 channels)
    {
        *size = width * height * channels;
        jpg = new unsigned char[*size];
        stbi_write_jpg_to_func([](void* context, void* data, int size) {
            unsigned char* jpg = (unsigned char*) context;
            memcpy(jpg, data, size);
            jpg += size;
        }, jpg, width, height, channels, data, quality);
    }
    return jpg;
}
