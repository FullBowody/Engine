#pragma once
#include <vector>
#include "Struct/Marker.hpp"

class DLLExport Scene: public Nullable
{
private:
    std::vector<Marker*> markers;

public:
    Scene();
    Scene(const Scene& other);
    ~Scene();

    int loadFromJSON(const std::string& filename);

    virtual Marker* createMarker(int id, Pose pose);
    virtual void destroyMarker(int index);
    virtual Marker* getMarker(int index) const;
    virtual Marker* findMarker(int id) const;
    virtual const std::vector<Marker*>& getMarkers() const;
};
