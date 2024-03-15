#pragma once

class Frame
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

    const unsigned char* getData() const;
    const int getWidth() const;
    const int getHeight() const;
    const int getChannels() const;
};
