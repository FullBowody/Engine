#include "common.hpp"

Position::Position()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Position::Position(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Position::~Position()
{
}

float Position::getX()
{
    return this->x;
}

float Position::getY()
{
    return this->y;
}

float Position::getZ()
{
    return this->z;
}

void Position::setX(float x)
{
    this->x = x;
}

void Position::setY(float y)
{
    this->y = y;
}

void Position::setZ(float z)
{
    this->z = z;
}

bool Position::fromBuffer(std::vector<unsigned char> buff)
{
    if(buff.size() < sizeof(float) * 3)
        return false;

    this->x = *(float*)&buff[0];
    this->y = *(float*)&buff[sizeof(float)];
    this->z = *(float*)&buff[sizeof(float) * 2];

    return true;
}

std::vector<unsigned char> Position::toBuffer()
{
    std::vector<unsigned char> buff(sizeof(float) * 3);

    *(float*)&buff[0] = this->x;
    *(float*)&buff[sizeof(float)] = this->y;
    *(float*)&buff[sizeof(float) * 2] = this->z;

    return buff;
}

Rotation::Rotation()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = 0;
}

Rotation::Rotation(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Rotation::~Rotation()
{
}

float Rotation::getX()
{
    return this->x;
}

float Rotation::getY()
{
    return this->y;
}

float Rotation::getZ()
{
    return this->z;
}

float Rotation::getW()
{
    return this->w;
}

void Rotation::setX(float x)
{
    this->x = x;
}

void Rotation::setY(float y)
{
    this->y = y;
}

void Rotation::setZ(float z)
{
    this->z = z;
}

void Rotation::setW(float w)
{
    this->w = w;
}

bool Rotation::fromBuffer(std::vector<unsigned char> buff)
{
    if(buff.size() < sizeof(float) * 4)
        return false;

    this->x = *(float*)&buff[0];
    this->y = *(float*)&buff[sizeof(float)];
    this->z = *(float*)&buff[sizeof(float) * 2];
    this->w = *(float*)&buff[sizeof(float) * 3];

    return true;
}

std::vector<unsigned char> Rotation::toBuffer()
{
    std::vector<unsigned char> buff(sizeof(float) * 4);

    *(float*)&buff[0] = this->x;
    *(float*)&buff[sizeof(float)] = this->y;
    *(float*)&buff[sizeof(float) * 2] = this->z;
    *(float*)&buff[sizeof(float) * 3] = this->w;

    return buff;
}

std::string stringifyState(State state)
{
    switch (state)
    {
        case STATE_ERROR:   return "Error";
        case STATE_STOPPED: return "Stopped";
        case STATE_RUNNING: return "Running";
        default:            return "Unknown";
    }
}

std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
std::string base64_encode(unsigned char *buff, unsigned int len)
{
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (len--)
    {
        char_array_3[i++] = *(buff++);
        if (i == 3)
        {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i < 4); i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];

        while ((i++ < 3))
            ret += '=';
    }

    return ret;
}