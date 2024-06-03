#pragma once
#include <vector>
#include "Struct/Marker.hpp"

class DLLExport Scene: public Nullable
{
private:
    std::vector<Marker> markers;

public:
    Scene();
    Scene(const Scene& scene);
    ~Scene();

    int loadFromFile(const std::string& filename);

    virtual const Marker& getMarker(int id) const;
    virtual const std::vector<Marker>& getMarkers() const;
    virtual void addMarker(const Marker& marker);
    virtual void removeMarker(int id);
};
