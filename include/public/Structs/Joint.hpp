#pragma once
#include "Structs/Transform.hpp"

class DLLExport Joint
{
private:
    Transform m_transform;

public:
    Joint();
    ~Joint();

    friend std::ostream& operator<<(std::ostream& os, const Joint& skeleton);

    const Transform& getTransform() const;
    void setTransform(const Transform& transform);
};
