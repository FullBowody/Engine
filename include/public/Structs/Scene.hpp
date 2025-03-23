#pragma once
#include <vector>
#include "utils.hpp"
#include "Structs/Marker.hpp"

class ENGINE_API Scene
{
private:
    std::vector<std::shared_ptr<Marker>> markers;

public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual std::weak_ptr<Marker> getMarker(int index) const;
    virtual void destroyMarker(int index);
    virtual void destroyMarker(const Marker& marker);
    virtual void addMarker(std::shared_ptr<Marker> marker);
    virtual const std::vector<std::shared_ptr<Marker>>& getMarkers() const;
    virtual void clearMarkers();
    virtual size_t getMarkerCount() const;
};
