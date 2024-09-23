#pragma once
#include "utils.hpp"
#include "Struct/Nullable.hpp"

class DLLExport Frame: public Nullable
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

    virtual unsigned char* getData() const;
    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual int getChannels() const;

    virtual unsigned char* encodeJPG(int quality = 80, int* size = nullptr) const;
};
