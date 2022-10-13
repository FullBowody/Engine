#include "Camera.hpp"

class CameraManager {
private:
    static CameraManager* instance;

    std::string lastError = "";
    std::vector<Camera*> cameras;

public:
    static CameraManager* getInstance();

    CameraManager();
    Camera* getCamera(int id);
    bool addCamera(Camera* camera);
    bool removeCamera(int id);
    std::vector<Camera*> getCameras();
    std::string getLastError();

    void update(float dt);
};