#pragma once
#include <vector>
#include "Structs/Skeleton.hpp"
#include "Camera/Camera.hpp"

namespace SkeletonSolver
{
    Skeleton solveFromCameras(const std::vector<Camera>& cameras);
};
