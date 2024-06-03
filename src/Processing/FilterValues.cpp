#include <cmath>
#include "Processing/FilterValues.hpp"

namespace FilterValues
{
    Vec3f filter(const std::vector<Vec3f>& values) { return filter(values, FilterSettings()); }
    Vec3f filter(const std::vector<Vec3f>& values, FilterSettings settings)
    {
        Vec3f average = Vec3f();
        for (Vec3f v : values) average += v;
        average /= values.size();

        float variance = 0;
        for (Vec3f v : values) variance += (v - average).length();
        variance /= values.size();

        float standardDeviationBiased = sqrt(variance) * settings.SDThreshold;
        Vec3f res = Vec3f();
        int count = 0;
        for (Vec3f v : values)
        {
            if ((v - average).length() < standardDeviationBiased)
            {
                res += v;
                count++;
            }
        }

        return res / count;
    }

    Quaternion filter(const std::vector<Quaternion>& values) { return filter(values, FilterSettings()); }
    Quaternion filter(const std::vector<Quaternion>& values, FilterSettings settings)
    {
        Quaternion average = Quaternion();
        for (Quaternion q : values) average *= q;
        average /= values.size();
        
        float variance = 0;
        for (Quaternion q : values) variance += (q - average).length();
        variance /= values.size();

        float standardDeviationBiased = sqrt(variance) * settings.SDThreshold;
        Quaternion res = Quaternion();
        int count = 0;
        for (Quaternion q : values)
        {
            if ((q - average).length() < standardDeviationBiased)
            {
                res *= q;
                count++;
            }
        }

        return res / count;
    }

    Pose filter(const std::vector<Pose>& values) { return filter(values, FilterSettings()); }
    Pose filter(const std::vector<Pose>& values, FilterSettings settings)
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
};
