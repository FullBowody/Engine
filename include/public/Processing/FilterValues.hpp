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

        /**
         * @brief The threshold for the maximum amount of filtred values.
         * Default value is 0.5f, this means that if more than 50% of the values are filtered,
         * the result will fallback to the average.
         * The higher the value, the more values will be able to be filtered.
         * Values equal or behond 1.0f will force a fallback to the average.
        */
        float filterThreshold = 0.5f;
    } FilterSettings;

    template<typename T> T
    filter(const std::vector<T>& values, FilterSettings settings = FilterSettings());

    Pose filter(const std::vector<Pose>& values, FilterSettings settings = FilterSettings())
    {
        std::vector<Vec3f> positions;
        std::vector<Quaternion> rotations;

        for (Pose p : values)
        {
            positions.push_back(p.getPosition());
            rotations.push_back(p.getRotation());
        }

        return Pose(
            filter(positions, settings),
            filter(rotations, settings)
        );
    }
    
    template<typename T>
    T filter(const std::vector<T>& values, FilterSettings settings)
    {
        T average = T();
        for (T v : values) average += v;
        average /= values.size();

        float variance = 0;
        for (T v : values) variance += (v - average).length2();
        variance /= values.size();

        float standardDeviationBiased = sqrt(variance) * settings.SDThreshold;
        T res = T();
        int count = 0;
        for (T v : values)
        {
            if ((v - average).length() < standardDeviationBiased)
            {
                res += v;
                count++;
            }
        }

        if (count < values.size() * settings.filterThreshold)
            return average;

        return res / count;
    }
};
