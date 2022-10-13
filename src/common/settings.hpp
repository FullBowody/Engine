#include <string>
#include "./common.hpp"

namespace Settings
{
    const float CAMERA_UPDATE_LAPSE = 1.f / 30.f; // 30 FPS
    const float TRACKER_UPDATE_LAPSE = 1.f / 30.f; // 30 FPS
    const float NETWORK_UPDATE_LAPSE = 1.f / 10.f; // 10 FPS
    const unsigned char BODY_POS_SOLVE_METHOD = BODY_POS_SOLVE_METHOD_DEFAULT;

    bool loadFromFile(std::string path);
    bool saveToFile(std::string path);
}