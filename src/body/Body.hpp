#pragma once
#include <vector>
#include "./BodyJoint.hpp"

class Body {
private:
    static Body* instance;
    std::vector<BodyJoint> joints;

public:
    static Body* getInstance();
    
    Body();
    ~Body();
};