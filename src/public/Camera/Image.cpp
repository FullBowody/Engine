#include <iostream>
#include <memory.h>
#include "Camera/Image.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

Image::Image()
    : data(nullptr), width(0), height(0)
{
}

Image::Image(unsigned char* data, int width, int height, int channels)
    : width(width), height(height), channels(channels)
{
    this->data = new unsigned char[width * height * channels];
    memcpy(this->data, data, width * height * channels * sizeof(unsigned char));
}

Image::Image(const Image& image)
    : width(image.width), height(image.height), channels(image.channels)
{
    data = new unsigned char[width * height * channels];
    memcpy(data, image.data, width * height * channels * sizeof(unsigned char));
}

Image::~Image()
{
    if (data) delete[] data;
}

unsigned char* Image::getData() const
{
    return data;
}

int Image::getWidth() const
{
    return width;
}

int Image::getHeight() const
{
    return height;
}

int Image::getChannels() const
{
    return channels;
}

unsigned char* Image::encodeJPG(int quality, int* size) const
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
    else
    {
        std::cerr << "Cannot encode image with " << channels << " channels to JPG, should be 3" << std::endl;
    }
    return jpg;
}
