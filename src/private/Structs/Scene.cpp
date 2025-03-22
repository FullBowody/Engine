#include "Structs/Scene.hpp"

std::weak_ptr<Marker> Scene::getMarker(int index)
{
    return markers.at(index);
}

void Scene::destroyMarker(int index)
{
    markers.erase(markers.begin() + index);
}

void Scene::destroyMarker(const Marker& marker)
{
    markers.erase(std::remove_if(markers.begin(), markers.end(), [&marker](const std::shared_ptr<Marker>& mark) {
        return mark.get() == &marker;
    }), markers.end());
}

void Scene::addMarker(std::shared_ptr<Marker> marker)
{
    markers.push_back(marker);
}

const std::vector<std::shared_ptr<Marker>>& Scene::getMarkers()
{
    return markers;
}

void Scene::clearMarkers()
{
    markers.clear();
}

size_t Scene::getMarkerCount() const
{
    return markers.size();
}
