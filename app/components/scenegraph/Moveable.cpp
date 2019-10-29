#include <Moveable.hpp>

namespace rwc
{

Moveable::Moveable(const glm::vec3& translation, const glm::quat& rotation, const glm::vec3& scale)
    : mTranslation{translation}
    , mRotation{rotation}
    , mScale{scale}
    , mParentRotation{glm::quat(1.0, 0.0, 0.0, 0.0)}
    , mMMC{1.0}
    , mParentMMC{1.0}
    , mRefresh{true}
    , mAnimationChannelCustom{}
    , mAnimationChannelTranslation{}
    , mAnimationChannelRotation{}
    , mAnimationChannelScale{}
{
    // empty
}

Moveable::~Moveable() = default;

Moveable& Moveable::operator=(const Moveable&) = default;

Moveable::Moveable(const Moveable&) = default;

Moveable& Moveable::operator=(Moveable&&) = default;

Moveable::Moveable(Moveable&&) = default;

glm::vec3 Moveable::getTranslation() const
{
    return mTranslation;
}

void Moveable::moveTo(const glm::vec3& coordinates)
{
    mTranslation = coordinates;
    mRefresh = true;
}

void Moveable::moveToX(float distance)
{
    mTranslation.x = distance;
    mRefresh = true;
}

void Moveable::moveToY(float distance)
{
    mTranslation.y = distance;
    mRefresh = true;
}

void Moveable::moveToZ(float distance)
{
    mTranslation.z = distance;
    mRefresh = true;
}

void Moveable::moveBy(const glm::vec3& coordinates)
{
    mTranslation += coordinates;
    mRefresh = true;
}

void Moveable::moveByX(float distance)
{
    mTranslation.x += distance;
    mRefresh = true;
}

void Moveable::moveByY(float distance)
{
    mTranslation.y += distance;
    mRefresh = true;
}

void Moveable::moveByZ(float distance)
{
    mTranslation.z += distance;
    mRefresh = true;
}

void Moveable::moveInDirection(const glm::vec3& direction)
{
    mTranslation += glm::vec3(glm::mat4_cast(mRotation) * glm::vec4(direction, 1.0));
    mRefresh = true;
}

glm::vec3 Moveable::getScale() const
{
    return mScale;
}

void Moveable::scaleTo(float scale)
{
    mScale = glm::vec3(scale, scale, scale);
    mRefresh = true;
}

void Moveable::scaleTo(const glm::vec3& scale)
{
    mScale = scale;
    mRefresh = true;
}

void Moveable::scaleToX(float scale)
{
    mScale = glm::vec3(scale, mScale.y, mScale.z);
    mRefresh = true;
}

void Moveable::scaleToY(float scale)
{
    mScale = glm::vec3(mScale.x, scale, mScale.z);
    mRefresh = true;
}

void Moveable::scaleToZ(float scale)
{
    mScale = glm::vec3(mScale.x, mScale.y, scale);
    mRefresh = true;
}

glm::quat Moveable::getRotation() const
{
    return mRotation;
}

void Moveable::rotateTo(const glm::quat& rotation)
{
    mRotation = rotation;
    mRefresh = true;
}

void Moveable::rotateTo(const glm::vec3& axis, float angle)
{
    mRotation = glm::angleAxis(angle, glm::normalize(axis));
    mRefresh = true;
}

void Moveable::rotateByX(float angle)
{
    rotateBy(glm::vec3(1.0, 0.0, 0.0), angle);
    mRefresh = true;
}

void Moveable::rotateByY(float angle)
{
    rotateBy(glm::vec3(0.0, 1.0, 0.0), angle);
    mRefresh = true;
}

void Moveable::rotateByZ(float angle)
{
    rotateBy(glm::vec3(0.0, 0.0, 1.0), angle);
    mRefresh = true;
}

void Moveable::rotateBy(const glm::vec3& axisLine, float angle)
{
    const glm::vec3 axis(glm::mat4_cast(mRotation) * glm::vec4(glm::normalize(axisLine), 1.0) * sinf(angle / 2.0f));
    const float scalar = cosf(angle / 2.0f);
    const glm::quat offset(scalar, axis.x, axis.y, axis.z);

    mRotation = glm::normalize(offset * mRotation);
    mRefresh = true;
}

void Moveable::updateMatrixCache()
{
    mMMC = glm::translate(glm::mat4(1.0), mTranslation) * glm::mat4_cast(mRotation) * glm::scale(glm::mat4(1.0), mScale);
}

bool Moveable::isRefresh() const
{
    return mRefresh;
}

void Moveable::setRefresh(bool state)
{
    mRefresh = state;
}

glm::mat4 Moveable::getParentMMC() const
{
    return mParentMMC;
}

glm::quat Moveable::getParentRotation() const
{
    return mParentRotation;
}

void Moveable::attachCustomCallback(float durationSeconds, std::function<void(float)> action)
{
    std::get<CHANNEL_CURRENT_IDX>(mAnimationChannelCustom).push_back([this, durationSeconds, action](float deltaSeconds) {
        auto& timePassed = std::get<CHANNEL_TIME_LENGTH_IDX>(mAnimationChannelCustom);
        if (0.0f == durationSeconds) {
            return durationSeconds;
        }
        if (0.0f == timePassed) {
            action(0.0f);
        }
        timePassed += deltaSeconds;
        action(getPercentageDone(timePassed, durationSeconds));
        if (timePassed < durationSeconds) {
            return 0.0f;
        }
        float timeLeft = timePassed - durationSeconds;
        timePassed = 0;

        return timeLeft;
    });
}

void Moveable::waitInTime(float durationSeconds)
{
    std::get<CHANNEL_CURRENT_IDX>(mAnimationChannelCustom).push_back([this, durationSeconds](float deltaSeconds) {
        auto& timePassed = std::get<CHANNEL_TIME_LENGTH_IDX>(mAnimationChannelCustom);
        timePassed += deltaSeconds;
        if (timePassed <= durationSeconds) {
            return 0.0f;
        }
        float timeLeft = timePassed - durationSeconds;
        timePassed = 0;

        return timeLeft;
    });
}

void Moveable::moveBy(float durationSeconds, const glm::vec3& deltaMove, std::function<float(float)> ease)
{
    clearChannel(mAnimationChannelTranslation);
    std::get<CHANNEL_CURRENT_IDX>(mAnimationChannelTranslation).push_back(
        [this, durationSeconds, deltaMove, ease](float deltaSeconds) {
            auto& timePassed = std::get<CHANNEL_TIME_LENGTH_IDX>(mAnimationChannelTranslation);
            if (0.0f == timePassed) {
                std::get<CHANNEL_VALUE_IDX>(mAnimationChannelTranslation) = mTranslation;
            }
            timePassed += deltaSeconds;
            const float percentageDone = ease(getPercentageDone(timePassed, durationSeconds));
            moveTo(std::get<CHANNEL_VALUE_IDX>(mAnimationChannelTranslation) + percentageDone * deltaMove);
            if (timePassed <= durationSeconds) {
                return 0.0f;
            }
            float timeLeft = timePassed - durationSeconds;
            timePassed = 0;

            return timeLeft;
        });
}

void Moveable::moveTo(float durationSeconds, const glm::vec3& endTranslation, std::function<float(float)> ease)
{
    clearChannel(mAnimationChannelTranslation);
    std::get<CHANNEL_CURRENT_IDX>(mAnimationChannelTranslation).push_back(
        [this, durationSeconds, endTranslation, ease](float deltaSeconds) {
            auto& timePassed = std::get<CHANNEL_TIME_LENGTH_IDX>(mAnimationChannelTranslation);
            if (0.0f == timePassed) {
                std::get<CHANNEL_VALUE_IDX>(mAnimationChannelTranslation) = mTranslation;
            }
            timePassed += deltaSeconds;
            const glm::vec3 deltaMove = endTranslation - std::get<CHANNEL_VALUE_IDX>(mAnimationChannelTranslation);
            const float percentageDone = ease(getPercentageDone(timePassed, durationSeconds));
            moveTo(std::get<CHANNEL_VALUE_IDX>(mAnimationChannelTranslation) + percentageDone * deltaMove);
            if (timePassed <= durationSeconds) {
                return 0.0f;
            }
            float timeLeft = timePassed - durationSeconds;
            timePassed = 0;

            return timeLeft;
        });
}

void Moveable::scaleBy(float durationSeconds, const glm::vec3& deltaScale, std::function<float(float)> ease)
{
    clearChannel(mAnimationChannelScale);
    std::get<CHANNEL_CURRENT_IDX>(mAnimationChannelScale).push_back(
        [this, durationSeconds, deltaScale, ease](float deltaSeconds) {
            auto& timePassed = std::get<CHANNEL_TIME_LENGTH_IDX>(mAnimationChannelScale);
            auto& current = std::get<CHANNEL_VALUE_IDX>(mAnimationChannelScale);
            if (0.0f == timePassed) {
                current = mScale;
            }
            timePassed += deltaSeconds;
            const float percentageDone = ease(getPercentageDone(timePassed, durationSeconds));
            const glm::vec3 scale = current * ( deltaScale - glm::vec3(1.0) );
            scaleTo(current + percentageDone * scale);
            if (timePassed <= durationSeconds) {
                return 0.0f;
            }
            const float timeLeft = timePassed - durationSeconds;
            timePassed = 0;

            return timeLeft;
        });
}

void Moveable::scaleTo(float durationSeconds, const glm::vec3& endScale, std::function<float(float)> ease)
{
    clearChannel(mAnimationChannelScale);
    std::get<CHANNEL_CURRENT_IDX>(mAnimationChannelScale).push_back(
        [this, durationSeconds, endScale, ease](float deltaSeconds) {
            auto& timePassed = std::get<CHANNEL_TIME_LENGTH_IDX>(mAnimationChannelScale);
            auto& current = std::get<CHANNEL_VALUE_IDX>(mAnimationChannelScale);
            if (0.0f == timePassed) {
                current = mScale;
            }
            timePassed += deltaSeconds;
            const float percentageDone = ease(getPercentageDone(timePassed, durationSeconds));
            scaleTo(current + percentageDone * (endScale - current));
            if (timePassed <= durationSeconds) {
                return 0.0f;
            }
            const float timeLeft = timePassed - durationSeconds;
            timePassed = 0;

            return timeLeft;
        });
}

void Moveable::rotateBy(float durationSeconds, const glm::vec3& axis, const float endAngle, std::function<float(float)> ease)
{
    clearChannel(mAnimationChannelRotation);
    std::get<CHANNEL_CURRENT_IDX>(mAnimationChannelRotation).push_back(
        [this, durationSeconds, endAngle, axis, ease](float deltaSeconds) {
            auto& timePassed = std::get<CHANNEL_TIME_LENGTH_IDX>(mAnimationChannelRotation);
            auto current = std::get<CHANNEL_VALUE_IDX>(mAnimationChannelRotation);
            if (timePassed == 0.0f) {
                current = mRotation;
            }
            timePassed += deltaSeconds;
            const float percentageDone = ease(getPercentageDone(timePassed, durationSeconds));
            rotateTo(current);
            rotateTo(axis, percentageDone * endAngle);
            if (timePassed < durationSeconds) {
                return 0.0f;
            }
            float timeLeft = timePassed - durationSeconds;
            timePassed = 0;

            return timeLeft;
        });
}

void Moveable::rotateTo(float durationSeconds, const glm::vec3& axis, const float endAngle, std::function<float(float)> ease)
{
    clearChannel(mAnimationChannelRotation);
    const auto endAngleQuat = glm::angleAxis(endAngle, glm::normalize(axis));

    std::get<CHANNEL_CURRENT_IDX>(mAnimationChannelRotation).push_back(
        [this, durationSeconds, endAngleQuat, ease](float deltaSeconds) {
            auto& timePassed = std::get<CHANNEL_TIME_LENGTH_IDX>(mAnimationChannelRotation);
            auto& current = std::get<CHANNEL_VALUE_IDX>(mAnimationChannelRotation);
            if (timePassed == 0.0f) {
                current = mRotation;
            }
            timePassed += deltaSeconds;
            const float percentageDone = ease(getPercentageDone(timePassed, durationSeconds));

            rotateTo(glm::mix(current, endAngleQuat, percentageDone));
            if (timePassed < durationSeconds) {
                return 0.0f;
            }
            const float timeLeft = timePassed - durationSeconds;
            timePassed = 0;

            return timeLeft;
        });
}

template <class Container>
float Moveable::stepInTime(Container& container, float deltaTime) {
    if (std::get<CHANNEL_CURRENT_IDX>(container).empty()
        || std::get<CHANNEL_HANDLERS_IDX>(container) == std::get<CHANNEL_CURRENT_IDX>(container).size()) {
        return deltaTime;
    }
    float timeLeft = deltaTime;
    do {
        timeLeft = std::get<CHANNEL_CURRENT_IDX>(container)[std::get<CHANNEL_HANDLERS_IDX>(container)](timeLeft);
        if (timeLeft == 0.0f) {
            return 0.0f;
        }
        std::get<CHANNEL_TIME_LENGTH_IDX>(container) = 0.0f;
        if (++std::get<CHANNEL_HANDLERS_IDX>(container) < std::get<CHANNEL_CURRENT_IDX>(container).size()) {
            continue;
        }
        std::get<CHANNEL_HANDLERS_IDX>(container) = 0;
        std::get<CHANNEL_CURRENT_IDX>(container).clear();

        return timeLeft;
    } while(1);
}

bool Moveable::onTimePassed(float secondsPassed)
{
    const std::array <float, 4> timeLeft {
        stepInTime(mAnimationChannelCustom, secondsPassed)
        , stepInTime(mAnimationChannelTranslation, secondsPassed)
        , stepInTime(mAnimationChannelRotation, secondsPassed)
        , stepInTime(mAnimationChannelScale, secondsPassed)
    };
    return std::all_of(timeLeft.begin(), timeLeft.end(), [](float time) {
        return time > 0.0f;
    });
}

void Moveable::stop()
{
    clearChannel(mAnimationChannelCustom);
    clearChannel(mAnimationChannelTranslation);
    clearChannel(mAnimationChannelScale);
    clearChannel(mAnimationChannelRotation);
}

template float Moveable::stepInTime<Moveable::AnimationChannel<int>>(Moveable::AnimationChannel<int>& c, float deltaTime);
template float Moveable::stepInTime<Moveable::AnimationChannel<glm::vec3>>(Moveable::AnimationChannel<glm::vec3>& c, float deltaTime);
template float Moveable::stepInTime<Moveable::AnimationChannel<glm::quat>>(Moveable::AnimationChannel<glm::quat>& c, float deltaTime);

} // namespace rwc
