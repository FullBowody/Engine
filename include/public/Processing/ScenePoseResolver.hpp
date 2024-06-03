#pragma once
#include <vector>
#include "Struct/Pose.hpp"
#include "Struct/Marker.hpp"
#include "Struct/Scene.hpp"

namespace ScenePoseResolver
{
    Pose resolvePose(const Scene& scene, const std::vector<Marker>& markers);
};
