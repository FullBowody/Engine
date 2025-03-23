#include <iostream>
#include <vector>
#include <memory>
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
    std::memcpy(this->data, data, width * height * channels * sizeof(unsigned char));
}

Image::Image(const Image& image)
    : width(image.width), height(image.height), channels(image.channels)
{
    data = new unsigned char[width * height * channels];
    std::memcpy(data, image.data, width * height * channels * sizeof(unsigned char));
}

Image::~Image()
{
    if (data) delete[] data;
}

Image& Image::operator=(const Image& other)
{
    if (this != &other)
    {
        if (data) delete[] data;
        width = other.width;
        height = other.height;
        channels = other.channels;
        data = new unsigned char[width * height * channels];
        memcpy(data, other.data, width * height * channels * sizeof(unsigned char));
    }
    return *this;
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
        std::vector<unsigned char> jpgBuffer;
        stbi_write_jpg_to_func([](void* context, void* data, int size) {
            std::vector<unsigned char>* buffer = (std::vector<unsigned char>*)context;
            buffer->insert(buffer->end(), (unsigned char*)data, (unsigned char*)data + size);
        }, &jpgBuffer, width, height, channels, data, quality);
        *size = jpgBuffer.size();
        jpg = new unsigned char[*size];
        std::memcpy(jpg, jpgBuffer.data(), *size);
    }
    else
    {
        std::cerr << "Cannot encode image with " << channels << " channels to JPG, should be 3" << std::endl;
    }
    return jpg;
}
