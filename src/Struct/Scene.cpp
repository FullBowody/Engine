#include "Struct/Scene.hpp"

Scene::Scene()
    : markers()
{
}

Scene::Scene(const Scene& other)
    : Nullable(other), markers(other.markers)
{
}

Scene::~Scene()
{
}

int Scene::loadFromJSON(const std::string& filename)
{
    // TODO : Implement
    return 1;
}

Marker* Scene::getMarker(int index) const
{
    if (index < 0 || index >= markers.size())
        return nullptr;
    return markers.at(index);
}

Marker* Scene::findMarker(int id) const
{
    for (Marker* marker : markers)
    {
        if (marker->getId() == id)
        {
            return marker;
        }
    }
    return nullptr;
}

const std::vector<Marker*>& Scene::getMarkers() const
{
    return markers;
}

Marker* Scene::createMarker(int id, const Pose& pose)
{
    Marker* marker = new Marker(id, pose);
    markers.push_back(marker);
    return marker;
}

void Scene::destroyMarker(int index)
{
    if (index < 0 || index >= markers.size())
        return;
    delete markers.at(index);
    markers.erase(markers.begin() + index);
}
