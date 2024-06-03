#pragma once
#include "Processing/ScenePoseResolver.hpp"

Pose ScenePoseResolver::resolvePose(const Scene& scene, const std::vector<Marker>& cameraMarkers)
{
    if (cameraMarkers.empty())
        return Null<Pose>();

    std::vector<Marker> validCameraMarkers;
    for (Marker m : cameraMarkers)
    {
        const Marker& marker = scene.getMarker(m.getId());
        if (marker.isNull())
            continue;
        validCameraMarkers.push_back(marker);
    }

    if (validCameraMarkers.empty())
        return Null<Pose>();

    Marker& cameraMarker = validCameraMarkers[0];
    const Marker& sceneMarker = scene.getMarker(cameraMarker.getId());
    
    // calculate camera pose from markerPose in camera and in scene
    Quaternion baseMarkerRot = cameraMarker.getPose().getRotation();
    Quaternion camMarkerRot = sceneMarker.getPose().getRotation();
    Quaternion camRot = camMarkerRot * baseMarkerRot.inverse(); // camera rotation
    
    Vec3f baseMarkerPos = cameraMarker.getPose().getPosition();
    Vec3f camMarkerPos = sceneMarker.getPose().getPosition();
    Vec3f camPos = camMarkerPos - camRot * baseMarkerPos; // camera position
    
    return Pose(camPos, camRot); // TODO : Verify if this is correct
}
