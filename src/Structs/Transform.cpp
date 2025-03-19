#include "Structs/Transform.hpp"

Transform::Transform() {
    // TODO: Implement
}

Transform::Transform(const std::string& name) {
    // TODO: Implement
}

Transform::Transform(const std::string& name, const glm::vec3& position, const glm::quat& rotation) {
    // TODO: Implement
}

Transform::Transform(const Transform& other) {
    // TODO: Implement
}

Transform::~Transform() {
    // TODO: Implement
}

void Transform::setParent(Transform* parent) {
    // TODO: Implement
}

Transform* Transform::getParent() const {
    // TODO: Implement
    return nullptr;
}

void Transform::setLocalPosition(const glm::vec3& position) {
    // TODO: Implement
}

glm::vec3 Transform::getLocalPosition() const {
    // TODO: Implement
    return glm::vec3();
}

void Transform::setLocalRotation(const glm::quat& rotation) {
    // TODO: Implement
}

glm::quat Transform::getLocalRotation() const {
    // TODO: Implement
    return glm::quat();
}

glm::vec3 Transform::getGlobalPosition() {
    // TODO: Implement
    return glm::vec3();
}

glm::vec3 Transform::getGlobalPosition(const Transform& root) {
    // TODO: Implement
    return glm::vec3();
}

glm::quat Transform::getGlobalRotation() {
    // TODO: Implement
    return glm::quat();
}

glm::quat Transform::getGlobalRotation(const Transform& root) {
    // TODO: Implement
    return glm::quat();
}