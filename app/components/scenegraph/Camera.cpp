#include <Camera.hpp>

namespace rwc
{

Camera::Camera(
    const glm::vec3& position
    , vec2f resolution
    , const glm::quat& rotation
    , float fovy
    , float nearPlane
    , float farPlane)
    : Moveable(position, rotation)
    , mViewMatrix{1.0}
    , mProjectionMatrix{1.0}
    , mRefreshView(true)
    , mRefreshProjection(true)
    , mProjectionFovy(fovy)
    , mProjectionAspectRatio(resolution[0] / resolution[1])
    , mProjectionNearPlane(nearPlane)
    , mProjectionFarPlane(farPlane)
{
    updateView();
    updateProjection();
}

Camera::Camera()
    : Moveable(glm::vec3(0.0, 0.0, 1.0),  glm::quat(1.0, 0.0, 0.0, 0.0))
    , mViewMatrix{1.0}
    , mProjectionMatrix{1.0}
    , mRefreshView(true)
    , mRefreshProjection(true)
    , mProjectionFovy(glm::radians(90.0f))
    , mProjectionAspectRatio(1.0f)
    , mProjectionNearPlane(0.01f)
    , mProjectionFarPlane(100.0f)
{
    updateView();
    updateProjection();
}

inline void Camera::updateView() {
    updateMatrixCache();

    mViewMatrix = glm::lookAt(
        mTranslation
        , mTranslation + glm::vec3((glm::mat4_cast(mRotation) * glm::vec4(0.0, 0.0, -1.0, 1.0)))
        , glm::vec3((glm::mat4_cast(mRotation) * glm::vec4(0.0, 1.0, 0.0, 1.0)))
    );

    mRefreshView = false;
    mRefresh = false;
}

void Camera::update() {
    if (mRefreshProjection) {
        updateProjection();
    }

    if (mRefresh || mRefreshView) {
        updateView();
    }
}

void Camera::updateProjection() {
    mProjectionMatrix = glm::perspective(
        mProjectionFovy
        , mProjectionAspectRatio
        , mProjectionNearPlane
        , mProjectionFarPlane
    );
    mRefreshProjection = false;
}

glm::mat4 Camera::getEye() const {
    return mViewMatrix;
}

glm::mat4 Camera::getProjection() const {
    return mProjectionMatrix;
}

glm::mat4 Camera::getViewProjection() const {
    return mProjectionMatrix * mViewMatrix;
}

float Camera::getProjectionFovy() const {
    return mProjectionFovy;
}

float Camera::getProjectionAspectRatio() const {
    return mProjectionAspectRatio;
}

float Camera::getProjectionNearPlane() const {
    return mProjectionNearPlane;
}

float Camera::getProjectionFarPlane() const {
    return mProjectionFarPlane;
}

void Camera::setProjectionFovy(float fovy) {
    mProjectionFovy = fovy;
    mRefreshProjection = true;
}

void Camera::setProjectionAspectRatio(float aspect) {
    mProjectionAspectRatio = aspect;
    mRefreshProjection = true;
}

void Camera::setProjectionNearPlane(float nearPlane) {
    mProjectionNearPlane = nearPlane;
    mRefreshProjection = true;
}

void Camera::setProjectionFarPlane(float farPlane) {
    mProjectionFarPlane = farPlane;
    mRefreshProjection = true;
}

} // namespace rwc