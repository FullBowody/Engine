#pragma once
#include "Processing/ScenePoseResolver.hpp"

Pose ScenePoseResolver::resolvePose(const Scene& scene, const std::vector<Marker>& cameraMarkers)
{
    if (cameraMarkers.empty())
        return Null<Pose>();

    std::vector<Marker> validCameraMarkers;
    for (Marker cameraMarker : cameraMarkers)
    {
        Marker* sceneMarker = scene.findMarker(cameraMarker.getId());
        if (sceneMarker == nullptr) continue;
        validCameraMarkers.push_back(cameraMarker);
    }

    if (validCameraMarkers.empty())
        return Null<Pose>();

    // TODO : Maybe use multiple markers to get a more accurate pose
    Marker& cameraMarker = validCameraMarkers[0];
    Marker& sceneMarker = *scene.findMarker(cameraMarker.getId());
    
    // get marker pos / rot in camera space
    Quaternion markerRot_cam = cameraMarker.getPose().getRotation();
    Vec3f markerPos_cam = cameraMarker.getPose().getPosition();

    // retreive camera pos / rot in marker space
    Quaternion cameraRot_marker = markerRot_cam.conjugate();
    Vec3f cameraPos_marker = -(cameraRot_marker * markerPos_cam);

    // get marker pos / rot in scene space
    Quaternion markerRot_scene = sceneMarker.getPose().getRotation();
    Vec3f markerPos_scene = sceneMarker.getPose().getPosition();

    // retreive camera pos / rot in scene space
    Quaternion cameraRot_scene = markerRot_scene * cameraRot_marker;
    Vec3f cameraPos_scene = markerRot_scene * cameraPos_marker + markerPos_scene;

    return Pose(cameraPos_scene, cameraRot_scene); // FIXME : Above calculations seems to be wrong
}
