#pragma once
#include "utils.hpp"

class DLLExport Image
{
protected:
    unsigned char* data;
    int width;
    int height;
    int channels;

public:
    Image();
    Image(unsigned char* data, int width, int height, int channels);
    Image(const Image& frame);
    ~Image();

    virtual unsigned char* getData() const;
    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual int getChannels() const;

    virtual unsigned char* encodeJPG(int quality = 80, int* size = nullptr) const;
};
