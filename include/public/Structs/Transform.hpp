#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "utils.hpp"

class DLLExport Transform {
public:
    Transform();
    Transform(const std::string& name);
    Transform(const std::string& name, const glm::vec3& position, const glm::quat& rotation);
    Transform(const Transform& other);
    ~Transform();

    void setParent(Transform* parent);
    Transform* getParent() const;

    void setLocalPosition(const glm::vec3& position);
    glm::vec3 getLocalPosition() const;

    void setLocalRotation(const glm::quat& rotation);
    glm::quat getLocalRotation() const;

    glm::vec3 getGlobalPosition();
    glm::vec3 getGlobalPosition(const Transform& root);

    glm::quat getGlobalRotation();
    glm::quat getGlobalRotation(const Transform& root);

private:
    std::string m_name;
    glm::vec3 m_position;
    glm::quat m_rotation;
    Transform* m_parent;
    std::vector<Transform&> m_children;
    bool m_outdated;

    glm::vec3 m_global_position;
    glm::quat m_global_rotation;
};
