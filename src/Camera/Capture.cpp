#include "Camera/Capture.hpp"
#include <iostream>

Capture::Capture()
{
    
}

Capture::~Capture()
{
    
}

int Capture::getWidth() const
{
    return width;
}

int Capture::getHeight() const
{
    return height;
}

int Capture::getFps() const
{
    return fps; // TODO : update that with the real fps (at update)
}
