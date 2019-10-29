#pragma once

#include <algorithm>
#include <functional>
#include <vector>

#include <Math.hpp>

namespace rwc
{

/*!
 * @class Moveable
 *
 * @brief This class encapsulates 3d object transformations and motion
 *
 * @param[in] translation initial position in model space
 *
 * @param[in] rotation initial rotation in model space
 *
 */

class Moveable
{
private:
    static constexpr unsigned CHANNEL_VALUE_IDX = 0;
    static constexpr unsigned CHANNEL_CURRENT_IDX = 1;
    static constexpr unsigned CHANNEL_HANDLERS_IDX = 2;
    static constexpr unsigned CHANNEL_TIME_LENGTH_IDX = 3;

public:
    explicit Moveable(
        const glm::vec3& translation = glm::vec3(0.0)
        , const glm::quat& rotation = glm::quat(1.0, 0.0, 0.0, 0.0)
        , const glm::vec3& scale = glm::vec3(1.0));

    virtual ~Moveable();

    Moveable& operator=(const Moveable&);
    Moveable(const Moveable&);
    Moveable& operator=(Moveable &&);
    Moveable(Moveable&&);

/*!
 * @brief Change the translation to a certain value
 *
 * @param[in] coordinates
 *
 */
    void moveTo(const glm::vec3& coordinates);

/*!
 * @brief Change the translation x component to a certain value
 *
 * @param[in] distance
 *
 */
    void moveToX(float distance);

/*!
 * @brief Change the translation y component to a certain value
 *
 * @param[in] distance
 *
 */
    void moveToY(float distance);

/*!
 * @brief Change the translation z component to a certain value
 *
 * @param[in] distance
 *
 */
    void moveToZ(float distance);

/*!
 * @brief Change the translation by a certain value
 *
 * @param[in] coordinates xyx
 *
 */
    void moveBy(const glm::vec3& coordinates);

/*!
 * @brief Change the translation x component by a certain value
 *
 * @param[in] distance
 *
 */
    void moveByX(float distance);

/*!
 * @brief Change the translation y component by a certain value
 *
 * @param[in] distance
 *
 */
    void moveByY(float distance);

/*!
 * @brief Change the translation z component by a certain value
 *
 * @param[in] distance
 *
 */
    void moveByZ(float distance);

/*!
 * @brief Change the translation by a specific direction by a certain value
 *
 * @param[in] direction
 *
 */
    void moveInDirection(const glm::vec3& direction);

/*!
 * @brief Returns the current tranformation translation value
 *
 */
    glm::vec3 getTranslation() const;

/*!
 * @brief Change the scale by a certain value
 *
 * @param[in] scale
 *
 */
    void scaleTo(float scale);

/*!
 * @brief Change the scale by a certain value specyfing each component separately
 *
 * @param[in] scale
 *
 */
    void scaleTo(const glm::vec3& scale);

/*!
 * @brief Change the scale x component to a certain value
 *
 * @param[in] scale
 *
 */
    void scaleToX(float scale);

/*!
 * @brief Change the scale y component to a certain value
 *
 * @param[in] scale
 *
 */
    void scaleToY(float scale);

/*!
 * @brief Change the scale z component to a certain value
 *
 * @param[in] scale
 *
 */
    void scaleToZ(float scale);

/*!
 * @brief Returns current scale value
 *
 * @return scale value
 *
 */
    glm::vec3 getScale() const;

/*!
 * @brief Change the rotation to a certain value using a quaternion
 *
 * @param[in] rotation expressed in quaternion
 *
 */
    void rotateTo(const glm::quat& rotation);

/*!
 * @brief Change the rotation to a certain value
 *
 * @param[in] axis along which the rotation will take place
 *
 * @param[in] angle expressed in radians
 *
 */
    void rotateTo(const glm::vec3& axis, float angle);

/*!
 * @brief Change the rotation by a certain value
 *
 * @param[in] axis along which the rotation will take place
 *
 * @param[in] angle expressed in radians
 *
 */
    void rotateBy(const glm::vec3& axis, float angle);

/*!
 * @brief Change the rotation by a certain value across x axis
 *
 * @param[in] angle
 *
 */
    void rotateByX(float angle);

/*!
 * @brief Change the rotation by a certain value across y axis
 *
 * @param[in] angle
 *
 */
    void rotateByY(float angle);

/*!
 * @brief Change the rotation by a certain value across z axis
 *
 * @param[in] angle
 *
 */
    void rotateByZ(float angle);

/*!
 * @brief Returns current rotation value
 *
 * @return rotation value expressed in quaternion
 *
 */
    glm::quat getRotation() const;

/*!
 * @brief Updates model cache according to current rotation, scale and translation values
 *
 */
    void updateMatrixCache();

/*!
 * @brief Checks if the models rotation, translation or scale was changed and the matrices were not yet upated
 *
 */
    bool isRefresh() const;

/*!
 * @brief Set explicit refresh flag to indicate we expect all transformation matrices to be recalculated
 *
 * @param[in] state
 *
 */
    void setRefresh(bool state);

/*!
 * @brief Get current model matrix cached value
 *
 * @param[in] model matrix cache
 *
 */
    glm::mat4 getParentMMC() const;


/*!
 * @brief Get rotation of its parent node
 *
 * @return rotation parent's rotation property
 *
 */
    glm::quat getParentRotation() const;


/*!
 * @brief Request a wait animation
 *
 * @param[in] deltaSeconds
 *
 */
    void waitInTime(float deltaSeconds);


/*!
 * @brief Change the transformation in a certain period of time by a specific value
 *
 * @param[in] durationSeconds
 *
 * @param[in] translation
 *
 * @param[in] ease easing function to be used
 *
 */
    void moveBy(
        float durationSeconds
        , const glm::vec3& translation
        , std::function<float(float)> ease = [](float x) { return x;} );

/*!
 * @brief Change the transformation in a certain period of time to a specific value
 *
 * @param[in] durationSeconds
 *
 * @param[in] endTranslation
 *
 * @param[in] ease
 *
 */
    void moveTo(
        float durationSeconds
        , const glm::vec3& endTranslation
        , std::function<float(float)> ease = [](float x) { return x;} );

/*!
 * @brief Change the scale in a certain period of time by a specific value
 *
 * @param[in] durationSeconds
 *
 * @param[in] scale
 *
 * @param[in] ease
 *
 */
    void scaleBy(
        float durationSeconds
        , const glm::vec3& scale
        , std::function<float(float)> ease = [](float x) { return x;} );

/*!
 * @brief Change the scale in a certain period of time to a specific value
 *
 * @param[in] durationSeconds
 *
 * @param[in] scale
 *
 * @param[in] ease
 *
 */
    void scaleTo(
        float durationSeconds
        , const glm::vec3& scale
        , std::function<float(float)> ease = [](float x) { return x;} );

/*!
 * @brief Change the rotation in a certain period of time by a specific value
 *
 * @param[in] durationSeconds
 *
 * @param[in] angle
 *
 * @param[in] axis
 *
 * @param[in] ease easing function to be used
 *
 */
    void rotateBy(
        float durationSeconds
        , const glm::vec3& axis
        , const float angle
        , std::function<float(float)> ease = [](float x) { return x;} );

/*!
 * @brief Change the scale in a certain period of time to a specific value
 *
 * @param[in] durationSeconds
 *
 * @param[in] axis
 *
 * @param[in] angle
 *
 * @param[in] ease easing function to be used
 *
 */
    void rotateTo(
        float durationSeconds
        , const glm::vec3& axis
        , const float angle
        , std::function<float(float)> ease = [](float x) { return x;} );

/*!
 * @brief Stops all ongoing transformation transitions
 *
 */
    void stop();

/*!
 * @brief Called every time when a time passed to keep all the internal transitions in sync
 *
 * @param[in] deltaSeconds
 *
 */
    bool onTimePassed(float deltaSeconds);

/*!
 * @brief Attached a specific function called every time frame until it ends
 *
 * @param[in] duration of the animation
 *
 * @param[in] action function to be executed when callback will be called
 *            function takes progress of the animation within 0.0f ... 1.0f
 *            for each element
 *
 */
    void attachCustomCallback(float durationSeconds, std::function<void(float)> action);

/*!
 * @brief check if There is an animation ongoing over this object
 *
 * @return return true if there is an animation ongoing
 *
 */
    inline constexpr bool isAnimating()
    {
        return
            std::get<CHANNEL_HANDLERS_IDX>(mAnimationChannelTranslation)
               + std::get<CHANNEL_HANDLERS_IDX>(mAnimationChannelScale)
               + std::get<CHANNEL_HANDLERS_IDX>(mAnimationChannelRotation)
               + std::get<CHANNEL_HANDLERS_IDX>(mAnimationChannelCustom) > 0;
    }

protected:
    glm::vec3 mTranslation;
    glm::quat mRotation;
    glm::vec3 mScale;

    /* Parent */
    glm::quat mParentRotation;

    /* MMC - Model Matrix Cache */
    glm::mat4 mMMC;
    glm::mat4 mParentMMC;

    /* Refresh flag */
    bool mRefresh;

private:
    template <class TKeyValue>
    using AnimationChannel = std::tuple<TKeyValue, std::vector<std::function<float(float)>>, unsigned, float>;
    AnimationChannel<int> mAnimationChannelCustom;
    AnimationChannel<glm::vec3> mAnimationChannelTranslation;
    AnimationChannel<glm::quat> mAnimationChannelRotation;
    AnimationChannel<glm::vec3> mAnimationChannelScale;

/*!
 * @brief Attached a custom function called every time when an onTimePassed function is called
 *
 * @param[in] container
 *
 * @param[in] deltaTime
 *
 */
    template <class Container>
    float stepInTime(Container& container, float deltaTime);

/*!
 * @brief Get the channel animation progress in the range of 0.0f .... 1.0f
 *
 * @param[in] timeSeconds how much time passed since handler started its execution
 *
 * @param[in] timeDurationSeconds how much time should the handler last
 *
 */
    inline constexpr float getPercentageDone(float timeSeconds, float timeDurationSeconds)
    {
        const float progress = timeSeconds / timeDurationSeconds;
        return progress >= 1.0f ? 1.0f : progress;
    }

/*!
 * @brief Performs the clean up of single animation channel
 *
 * @param[in] channel
 *
 */
    template <class TChannel>
    inline void clearChannel(TChannel& channel)
    {
        std::get<CHANNEL_CURRENT_IDX>(channel).clear();
        std::get<CHANNEL_HANDLERS_IDX>(channel) = 0;
        std::get<CHANNEL_TIME_LENGTH_IDX>(channel) = 0;
    }
};

} // namespace rwc
