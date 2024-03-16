#include "Tracker/ArucoTracker.hpp"
#include <opencv2/core.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/calib3d.hpp> // TODO : Not sure if this is needed

ArucoTracker::ArucoTracker()
{
    
}

ArucoTracker::~ArucoTracker()
{

}

const Vec3f ArucoTracker::getTrackedPosition() const
{
    return this->position;
}

const Quaternion ArucoTracker::getTrackedRotation() const
{
    return this->rotation;
}

void ArucoTracker::onEvent(const CameraFrameEvent& event)
{
    const Frame& f = event.getData().getFrame();
    cv::Mat frame = cv::Mat(f.getHeight(), f.getWidth(), CV_8UC3, (void*)f.getData());

    // TODO: those things should be taken from somewhere else (settings?)
    cv::Ptr<cv::aruco::Dictionary> dict = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);
    cv::Ptr<cv::aruco::DetectorParameters> parameters = cv::aruco::DetectorParameters::create();
    cv::Ptr<cv::aruco::GridBoard> board = cv::aruco::GridBoard::create(3, 2, 0.0876, 0.005, dict, 0);

    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f>> corners;
    std::vector<std::vector<cv::Point2f>> rejected;

    cv::aruco::detectMarkers(
        frame,
        dict,
        corners,
        ids,
        parameters,
        rejected
    );

    cv::Mat camMatrix = (cv::Mat1d(3, 3) << 1, 0, 0, 0, 1, 0, 0, 0, 1);
    cv::Mat distCoeffs = cv::Mat::zeros(5, 1, CV_64F);

    cv::Mat rotation, translation;

    cv::aruco::estimatePoseBoard(
        corners,
        ids,
        board,
        camMatrix,
        distCoeffs,
        rotation,
        translation
    );

    this->position = Vec3f(
        translation.at<float>(0, 0),
        translation.at<float>(1, 0),
        translation.at<float>(2, 0)
    );

    cv::Mat rotMat(3, 3, CV_32F);
    cv::Rodrigues(rotation, rotMat);

    this->rotation = Quaternion::FromRotationMatrix(rotMat.data);
}
