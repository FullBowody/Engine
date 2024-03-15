#pragma once

class Frame
{
public:
    unsigned char* data;
    int width;
    int height;

    Frame();
    Frame(unsigned char* data, int width, int height);
    Frame(const Frame& frame);
    ~Frame();
};
