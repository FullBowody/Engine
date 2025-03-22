#pragma once
#include "Structs/Transform.hpp"
#include "utils.hpp"

class ENGINE_API Joint
{
private:
    Transform transform;

public:
    Joint();
    virtual ~Joint();

    friend std::ostream& operator<<(std::ostream& os, const Joint& skeleton);

    virtual const Transform& getTransform() const;
    virtual void setTransform(const Transform& transform);
};
