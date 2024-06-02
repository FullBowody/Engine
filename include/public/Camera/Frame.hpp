#pragma once
#include "utils.hpp"

class DLLExport Frame
{
protected:
    unsigned char* data;
    int width;
    int height;
    int channels;

public:
    Frame();
    Frame(unsigned char* data, int width, int height, int channels);
    Frame(const Frame& frame);
    ~Frame();

    virtual const unsigned char* getData() const;
    virtual const int getWidth() const;
    virtual const int getHeight() const;
    virtual const int getChannels() const;

    virtual unsigned char* encodeJPG(int quality = 80, int* size = nullptr) const;
};
