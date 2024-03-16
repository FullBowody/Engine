#include "Tracker/BodyTracker.hpp"

BodyTracker::BodyTracker()
{
    
}

BodyTracker::~BodyTracker()
{

}

void BodyTracker::onEvent(const CameraFrameEvent& event)
{

}

const Body2D BodyTracker::getTrackedBody() const
{
    return body;
}
