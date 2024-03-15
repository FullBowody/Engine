#include <iostream>
#include "Camera/Frame.hpp"

Frame::Frame()
    : data(nullptr), width(0), height(0)
{

}

Frame::Frame(unsigned char* data, int width, int height)
    : width(width), height(height)
{
    std::cout << "Frame created at address : " << this << std::endl;
}

Frame::Frame(const Frame& frame)
    : data(frame.data), width(frame.width), height(frame.height)
{
    std::cout << "Copying frame of size " << frame.width << "x" << frame.height << std::endl;
    std::cout << "Object address : " << this << std::endl;
}

Frame::~Frame()
{
    
}
