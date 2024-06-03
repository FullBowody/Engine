#include "Struct/Scene.hpp"

Scene::Scene()
    : markers()
{
}

Scene::Scene(const Scene& scene)
    : markers(scene.markers)
{
}

Scene::~Scene()
{
}

int Scene::loadFromFile(const std::string& filename)
{
    // TODO : Implement
    return 1;
}

Marker Scene::getMarker(int id) const
{
    for (const Marker& marker : markers)
    {
        if (marker.getId() == id)
        {
            return marker;
        }
    }
    return Null<Marker>();
}

const std::vector<Marker>& Scene::getMarkers() const
{
    return markers;
}

void Scene::addMarker(Marker marker)
{
    markers.push_back(marker);
}

void Scene::removeMarker(int id)
{
    for (auto it = markers.begin(); it != markers.end(); ++it)
    {
        if (it->getId() == id)
        {
            markers.erase(it);
            break;
        }
    }
}
