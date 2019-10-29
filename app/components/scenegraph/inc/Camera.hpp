#pragma once

#include <Moveable.hpp>

namespace rwc
{

/*! \class Camera
 *
 * \brief Stores camera view parameters.
 *
 */
class Camera : public Moveable
{
public:
    Camera();

    Camera(
        const glm::vec3& position
        , vec2f resolution
        , const glm::quat& rotation = glm::quat{1.0, 0.0, 0.0, 0.0}
        , float fovy = glm::radians(90.0f)
        , float nearPlane = 0.01f
        , float farPlane = 100.0f);

    ~Camera() override = default;

/*!
 * @brief Updates view and perspective matrices according to current camera parameters
 *
 */
    void update();

/*!
 * @brief Updates view matrix according to current view parameters (position and rotation)
 *
 */
    void updateView();

/*!
 * @brief Updates projection matrix according to current projection parameters
 *        (field of view, near plane, far plane and aspect ratio)
 *
 */
    void updateProjection();

/*!
 * @brief Get the current camera view matrix without upating it
 *
 * @return View matrix
 *
 */
    glm::mat4 getEye() const;

/*!
 * @brief Get the current camera projection matrix without updating it first
 *
 * @return Projection matrix
 *
 */
    glm::mat4 getProjection() const;

/*!
 * @brief Get the current camera projection matrix without updating it
 *
 * @return Projection * View matrix
 *
 */
    glm::mat4 getViewProjection() const;

/*!
 * @brief Get field of view projection parameter
 *
 * @return Field of view projection parameter
 *
 */
    float getProjectionFovy() const;

/*!
 * @brief Get the aspect ratio projection paramter
 *
 * @return Aspect ratio projection parameter (width/height)
 *
 */
    float getProjectionAspectRatio() const;

/*!
 * @brief Get the near plane of the projection
 *
 * @return Near plane projection parameter
 *
 */
    float getProjectionNearPlane() const;

/*!
 * @brief Get the far plane of the projection
 *
 * @return Far plane projection parameter
 *
 */
    float getProjectionFarPlane() const;

/*!
 * @brief Set the projection field of view
 *
 * @param fovy projection field of view
 *
 */
    void setProjectionFovy(float fovy);

/*!
 * @brief Set the projection aspect ratio
 *
 * @param aspectRatio projection aspect ratio
 *
 */
    void setProjectionAspectRatio(float aspectRatio);

/*!
 * @brief Set the near plane of the projection
 *
 * @param projection near plane
 *
 */
    void setProjectionNearPlane(float nearPlane);

/*!
 * @brief Set the projection field of view
 *
 * @param fovy projection field of view
 *
 */
    void setProjectionFarPlane(float farPlane);

 protected:
    glm::mat4 mViewMatrix;
    glm::mat4 mProjectionMatrix;

    bool mRefreshView;
    bool mRefreshProjection;

    float mProjectionFovy;
    float mProjectionAspectRatio;
    float mProjectionNearPlane;
    float mProjectionFarPlane;
};

} // namespace rwc
