#pragma once
#include "ScenePoseResolver.hpp"

Pose ScenePoseResolver::resolvePose(const Scene& scene, const std::vector<Marker>& markers)
{
    if (markers.empty())
        return Null<Pose>();

    std::vector<const Marker&> markersInScene;
    for (const Marker& marker : markers)
    {
        const Marker& marker = scene.getMarker(marker.getId());
        if (marker.isNull())
            continue;
        markersInScene.push_back(marker);
    }

    if (markersInScene.empty())
        return Null<Pose>();

    // TODO : Find a way to use multiple markers with confidence weights
    //        For the moment, we only use the first marker

    return Pose(); // TODO : Implement
}
