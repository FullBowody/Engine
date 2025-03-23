#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "utils.hpp"

class ENGINE_API Transform
{
private:
    std::string name;
    glm::vec3 position;
    glm::quat rotation;
    std::shared_ptr<Transform> parent;
    std::vector<Transform*> children;
    bool outdated;

    glm::vec3 global_position;
    glm::quat global_rotation;

    void calculateGlobalPositionRotation();

    void markOutdatedRecursive();
    void addChild(Transform* child);
    void removeChild(Transform* child);

public:
    Transform();
    Transform(const std::string& name);
    Transform(const std::string& name, const glm::vec3& position, const glm::quat& rotation);
    ~Transform();

    friend std::ostream& operator<<(std::ostream& os, const Transform& transform);

    void setParent(std::shared_ptr<Transform> parent, bool keepGlobalPosition = true);
    std::shared_ptr<Transform> getParent() const;

    std::vector<std::weak_ptr<Transform>> getChildren() const;

    void setLocalPosition(const glm::vec3& position);
    glm::vec3 getLocalPosition() const;

    void setLocalRotation(const glm::quat& rotation);
    glm::quat getLocalRotation() const;

    glm::vec3 getGlobalPosition();
    glm::vec3 getGlobalPosition(Transform& root);

    glm::quat getGlobalRotation();
    glm::quat getGlobalRotation(Transform& root);

    Transform getGlobalTransform();
    Transform getGlobalTransform(Transform& root);

    Transform getInverse() const;
};
