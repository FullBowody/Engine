#pragma once
#include <vector>
#include "Struct/Vec3.hpp"
#include "Struct/Vec2.hpp"
#include "Struct/Quaternion.hpp"
#include "Struct/Pose.hpp"

namespace FilterValues
{
    typedef struct FilterSettings
    {
        /**
         * @brief The threshold for the standard deviation to filter the values.
         * Default value is 1.0f, this means that values behond 1.0fs * [standard deviation] will be ignored.
         * The higher the value, the more extreme values will be taken into account.
        */
        float SDThreshold = 1.0f;
    } FilterSettings;

    Vec3f filter(const std::vector<Vec3f>& values);
    Vec3f filter(const std::vector<Vec3f>& values, FilterSettings settings);

    Quaternion filter(const std::vector<Quaternion>& values);
    Quaternion filter(const std::vector<Quaternion>& values, FilterSettings settings);

    Pose filter(const std::vector<Pose>& values);
    Pose filter(const std::vector<Pose>& values, FilterSettings settings);
};
