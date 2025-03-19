#pragma once
#include <string>
#include <ostream>
#include <functional>
#include "Structs/Identifiable.hpp"
#include "Updatable.hpp"
#include "Structs/FBError.hpp"
#include "Camera/Capture.hpp"

class DLLExport Camera: public Identifiable, public Updatable
{
private:
    std::string m_name;
    Capture* m_capture;

public:
    Camera();
    Camera(const Capture* capture);
    Camera(const Camera& camera);
    virtual ~Camera();

    Camera& operator=(const Camera& other);
    bool operator==(const Camera& other) const;
    bool operator!=(const Camera& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Camera& camera);

    virtual const Capture* getCapture() const;
    virtual void setCapture(Capture* capture);
    
    virtual FBError onUpdate(float dt);
};
