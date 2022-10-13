#pragma once
#include <string>
#include <vector>

class Position {
private:
    float x;
    float y;
    float z;
public:
    Position();
    Position(float x, float y, float z);
    ~Position();

    float getX();
    float getY();
    float getZ();

    void setX(float x);
    void setY(float y);
    void setZ(float z);

    bool fromBuffer(std::vector<unsigned char> buff);
    std::vector<unsigned char> toBuffer();
};

class Rotation {
private:
    float x;
    float y;
    float z;
    float w;
public:
    Rotation();
    Rotation(float x, float y, float z, float w);
    ~Rotation();

    float getX();
    float getY();
    float getZ();
    float getW();

    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void setW(float w);

    bool fromBuffer(std::vector<unsigned char> buff);
    std::vector<unsigned char> toBuffer();
};

typedef unsigned short State;
typedef unsigned short Port;

const Port DEFAULT_PORT = 5621;

const State STATE_ERROR = 0;
const State STATE_STOPPED = 1;
const State STATE_RUNNING = 2;

const Position DEFAULT_POSITION(0.f, 0.f, 0.f);
const Rotation DEFAULT_ROTATION(0.f, 0.f, 0.f, 0.f);

const unsigned char BODY_POS_SOLVE_METHOD_INTERSECTIONS = 1; // use intersections for body z position
const unsigned char BODY_POS_SOLVE_METHOD_IA_Z_GUESS = 2; // use IA to guess Z on each camera
const unsigned char BODY_POS_SOLVE_METHOD_COMBINE = 3; // use IA Z guess + intersections
const unsigned char BODY_POS_SOLVE_METHOD_DEFAULT = BODY_POS_SOLVE_METHOD_INTERSECTIONS;

std::string stringifyState(State state);
std::string base64_encode(unsigned char* buff, unsigned int len);