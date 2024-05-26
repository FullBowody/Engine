#pragma once
#include <string>
#include <functional>
#include "Event/EventManager.hpp"
#include "Updatable.hpp"
#include "Struct/Vec3.hpp"
#include "Struct/Quaternion.hpp"

class Camera: public Updatable
{
protected:
    Vec3f position;
    Quaternion rotation;

public:
    Camera();
    ~Camera();
    virtual int update(float dt);
    virtual int getWidth() const;
    virtual int getHeight() const;
};
