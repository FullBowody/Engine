#pragma once
#include <string>
#include <ostream>
#include <functional>
#include "Identifiable.hpp"
#include "Updatable.hpp"
#include "Structs/FBError.hpp"
#include "Camera/Capture.hpp"

class DLLExport Camera: public Identifiable, public Updatable
{
private:
    std::string m_name;
    std::shared_ptr<Capture> m_capture;

public:
    Camera();
    Camera(std::shared_ptr<Capture> capture);
    virtual ~Camera();

    friend std::ostream& operator<<(std::ostream& os, const Camera& camera);

    virtual const std::string& getName() const;
    virtual void setName(const std::string& name);

    virtual std::weak_ptr<Capture> getCapture() const;
    virtual void setCapture(std::shared_ptr<Capture> capture);

    virtual FBError startTracking();
    virtual FBError stopTracking();

    virtual FBError startPreview();
    virtual FBError stopPreview();

    virtual FBError onUpdate(float dt);
};
