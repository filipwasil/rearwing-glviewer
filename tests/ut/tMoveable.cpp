#include <catch/catch.hpp>
#include <Moveable.hpp>

using rwc::Moveable;

TEST_CASE("onTimePassed method tests", "[Moveable]")
{
    Moveable sut;
    SECTION("One waiting step introduced but not enough time passed for it to finish")
    {
        sut.waitInTime(1.1f);
        CHECK(sut.onTimePassed(1.0f) == false);
    }

    SECTION("Two waiting steps introduced but ony one finished")
    {
        sut.waitInTime(1.1f);
        sut.waitInTime(1.1f);
        CHECK(sut.onTimePassed(1.0f) == false);
    }

    SECTION("Two waiting steps introduced and both finished")
    {
        sut.waitInTime(1.1f);
        sut.waitInTime(1.1f);
        CHECK(sut.onTimePassed(3.0f) == true);
    }

    SECTION("Two waiting steps introduced and after ten time periods all finished")
    {
        sut.waitInTime(100.1f);
        sut.waitInTime(1.1f);
        CHECK(sut.onTimePassed(11.0f) == false);
        CHECK(sut.onTimePassed(2.0f) == false);
        CHECK(sut.onTimePassed(4.0f) == false);
        CHECK(sut.onTimePassed(6.0f) == false);
        CHECK(sut.onTimePassed(10.0f) == false);
        CHECK(sut.onTimePassed(30.0f) == false);
        CHECK(sut.onTimePassed(30.0f) == false);
        CHECK(sut.onTimePassed(3.0f) == false);
        CHECK(sut.onTimePassed(30.0f) == true);
    }

    SECTION("One waiting steps introduced and instantly finished after first time period passed")
    {
        sut.waitInTime(1.1f);
        CHECK(sut.onTimePassed(3.0f) == true);
    }

    SECTION("One move step introduced but not enough time passed for it to finish")
    {
        sut.moveBy(1.1f, glm::vec3(-0.1, 0.1, 0.2));
        CHECK(sut.onTimePassed(1.0f) == false);
    }

    SECTION("Two move steps introduced but ony one finished")
    {
        sut.moveBy(1.1f, glm::vec3(0.1, -0.1, 0.2));
        sut.moveBy(1.1f, glm::vec3(-0.1, 0.1, -0.2));
        CHECK(sut.onTimePassed(1.0f) == false);
    }

    SECTION("Two move steps introduced and both finished")
    {
        sut.moveBy(1.1f, glm::vec3(0.1, 0.1, -0.2));
        sut.moveBy(1.1f, glm::vec3(0.1, -0.1, 0.2));
        CHECK(sut.onTimePassed(3.0f) == true);
    }

    SECTION("Wait and move steps introduced and after ten time periods all finished")
    {
        sut.waitInTime(100.1f);
        sut.moveBy(1.1f, glm::vec3(0.1, 0.1, 0.2));
        CHECK(sut.onTimePassed(11.0f) == false);
        CHECK(sut.onTimePassed(2.0f) == false);
        CHECK(sut.onTimePassed(4.0f) == false);
        CHECK(sut.onTimePassed(6.0f) == false);
        CHECK(sut.onTimePassed(10.0f) == false);
        CHECK(sut.onTimePassed(30.0f) == false);
        CHECK(sut.onTimePassed(30.0f) == false);
        CHECK(sut.onTimePassed(3.0f) == false);
        CHECK(sut.onTimePassed(30.0f) == true);
    }

    SECTION("One move steps introduced and instantly finished after first time period passed")
    {
        sut.moveBy(1.1f, glm::vec3(0.1, 0.1, 0.2));
        CHECK(sut.onTimePassed(3.0f) == true);
    }

    SECTION("Wait, move and scale steps introduced and after one time periods all finished")
    {
        sut.waitInTime(1.1f);
        sut.moveBy(1.1f, glm::vec3(0.1, 0.1, 0.2));
        sut.scaleBy(1.1f, glm::vec3(0.1, 0.1, 0.2));
        CHECK(sut.onTimePassed(1.10001f) == true);
    }

    SECTION("One scale step introduced and instantly finished after first time period passed")
    {
        sut.scaleBy(1.1f, glm::vec3(0.1, 0.2, 0.3));
        CHECK(sut.onTimePassed(3.0f) == true);
    }

    SECTION("One scale step introduced but not enought time passed for it to be finished")
    {
        sut.scaleBy(1.1f, glm::vec3(0.1, 0.1, 0.2));
        CHECK(sut.onTimePassed(1.0f) == false);
    }

    SECTION("One scale step introduced and instantly finished after first time period passed")
    {
        sut.rotateBy(1.1f, glm::vec3(0.1, 0.2, 0.3), 180.0f);
        CHECK(sut.onTimePassed(3.0f) == true);
    }

    SECTION("One scale step introduced but not enought time passed for it to be finished")
    {
        sut.rotateBy(1.1f, glm::vec3(0.13, 0.1, 0.2), 180.0f);
        CHECK(sut.onTimePassed(1.0f) == false);
    }

    SECTION("One step each animation channel introduced and finished")
    {
        sut.rotateBy(1.1f, glm::vec3(0.13, 0.1, 0.2), 180.0f);
        sut.scaleBy(1.1f, glm::vec3(0.13, 1110.1, 0.2));
        sut.moveBy(1.1f, glm::vec3(122.13, 1110.1, 0.2));
        CHECK(sut.onTimePassed(1.0f) == false);
    }

    SECTION("Rotation introduced with zero degrees angle and one second passed")
    {
        sut.rotateBy(1.1f, glm::vec3(0.13, 0.1, 0.2), 0.0f);
        CHECK(glm::quat(1.0, 0.0, 0.0, 0.0) == sut.getRotation());
    }

    SECTION("Rotation introduced with zero angle angle and one second passed")
    {
        sut.rotateBy(1.1f, glm::vec3(0.13, 0.1, 0.2), 0.0f);
        CHECK(glm::quat(1.0, 0.0, 0.0, 0.0) == sut.getRotation());
    }

    SECTION("Rotation introduced with non-zero angle angle and one second passed")
    {
        sut.rotateBy(1.1f, glm::vec3(0.13, 0.1, 0.2), 120.0f);
        sut.onTimePassed(1.0f);
        CHECK(glm::quat(1.0, 0.0, 0.0, 0.0) != sut.getRotation());
    }

    Moveable sutRef;
    SECTION("Rotation changed instantly and after animation equal when full time passed")
    {
        sutRef.rotateTo(glm::vec3(1.0, 0.0, 0.0), 1.0f);
        sut.rotateBy(1.1f, glm::vec3(1.0, 0.0, 0.0), 1.0f);
        sut.onTimePassed(1.1f);
        CHECK(sutRef.getRotation() == sut.getRotation());
    }

    SECTION("Direct rotation change requested and half time passed")
    {
        sutRef.rotateTo(glm::vec3(1.0, 0.0, 0.0), 0.5f);
        sut.rotateBy(1.1f, glm::vec3(1.0, 0.0, 0.0), 1.0f);
        sut.onTimePassed(0.55f);
        CHECK(sutRef.getRotation() == sut.getRotation());
    }

    SECTION("Indirect rotation change requested in time domain and enough time passed")
    {
        sutRef.rotateBy(1.1f, glm::vec3(1.0, 0.0, 0.0), 2.0f);
        auto r1 = sutRef.getRotation();

        sutRef.onTimePassed(0.56f);
        auto r2 = sutRef.getRotation();

        sutRef.onTimePassed(0.56f);
        auto r3 = sutRef.getRotation();

        sutRef.onTimePassed(0.3f);
        auto r4 = sutRef.getRotation();

        CHECK(r1 != r2);
        CHECK(r2 != r3);
        CHECK(r3 == r4);
    }

    SECTION("Indirect rotation change requested in time domain and not enough time passed")
    {
        sutRef.rotateBy(1.1f, glm::vec3(1.0, 0.0, 0.0), 20.0f);
        auto r1 = sutRef.getRotation();

        sutRef.onTimePassed(0.24f);
        auto r2 = sutRef.getRotation();

        sutRef.onTimePassed(0.54f);
        auto r3 = sutRef.getRotation();

        sutRef.onTimePassed(0.33f);
        auto r4 = sutRef.getRotation();

        CHECK(r1 != r2);
        CHECK(r2 != r3);
        CHECK(r3 != r4);
    }

    SECTION("Direct rotation change requested in time domain and not enough time passed")
    {
        sutRef.rotateTo(1.1f, glm::vec3(1.0, 0.0, 0.0), 1.0f);
        auto r1 = sutRef.getRotation();

        sutRef.onTimePassed(0.3f);
        auto r2 = sutRef.getRotation();

        sutRef.onTimePassed(0.3f);
        auto r3 = sutRef.getRotation();

        sutRef.onTimePassed(0.3f);
        auto r4 = sutRef.getRotation();

        sutRef.onTimePassed(0.3f);
        auto r5 = sutRef.getRotation();

        sutRef.onTimePassed(0.3f);
        auto r6 = sutRef.getRotation();

        CHECK(r1 != r2);
        CHECK(r2 != r3);
        CHECK(r3 != r4);
        CHECK(r4 != r5);
        CHECK(r5 == r6);
    }

    SECTION("Move by zero position does not change the position after time")
    {
        sut.moveBy(1.1f, glm::vec3(0.0, 0.0, 0.0));
        sut.onTimePassed(100.0f);
        CHECK(sutRef.getTranslation() == sut.getTranslation());
    }

    SECTION("Move by non-zero position does not change the position after time")
    {
        sut.moveBy(1.1f, glm::vec3(0.0, 1.0, 0.0));
        sut.onTimePassed(100.0f);
        CHECK(sutRef.getTranslation() != sut.getTranslation());
    }

    SECTION("Changing scale instantly resulats in the same value when scaling with animation")
    {
        sutRef.scaleTo(glm::vec3(3.5, 4.0, 36.0));
        sut.scaleTo(1.1f, glm::vec3(2.5, 4.0, 36.0));
        sut.scaleTo(1.1f, glm::vec3(3.5, 4.0, 36.0));
        sut.onTimePassed(2.1f);
        CHECK(sut.onTimePassed(1.1f) == true);
        CHECK(sutRef.getScale() == sut.getScale());
    }

    SECTION("Got interrupted when performing scalechange in time")
    {
        sutRef.scaleTo(glm::vec3(2.5, 4.0, 36.0));
        sut.scaleBy(1.1f, glm::vec3(2.5, 4.0, 36.0));
        sut.onTimePassed(1.0f);
        sut.stop();
        sut.onTimePassed(1.1f);
        sut.onTimePassed(0.55f);
        sut.onTimePassed(1.1f);
        sut.onTimePassed(0.55f);
        CHECK(sutRef.getScale() != sut.getScale());
    }

    SECTION("Scale change requested and interrupted in the middle of second empty transition")
    {
        sutRef.scaleTo(glm::vec3(2.5, 4.0, 10.0));
        sut.scaleBy(1.1f, glm::vec3(1.0, 1.0, 1.0));
        sut.scaleBy(1.1f, glm::vec3(2.5, 4.0, 10.0));
        sut.onTimePassed(1.1f);
        sut.onTimePassed(0.55f);
        CHECK(sutRef.getScale() == sut.getScale());
    }

    SECTION("MoveTo and moveBy do the same changes when given the same paramters")
    {
        sutRef.moveTo(glm::vec3(1.0, 5.0, 10.0));
        sut.moveBy(1.1f, glm::vec3(1.0, 5.0, 10.0));
        sut.onTimePassed(1.1f);
        CHECK(sutRef.getTranslation() == sut.getTranslation());
    }

    SECTION("When stopped in the middle of the animation exactly half of translation change is done")
    {
        sutRef.moveTo(glm::vec3(0.5, 1.0, 2.0));
        sut.moveBy(1.1f, glm::vec3(1.0, 2.0, 4.0));
        sut.onTimePassed(0.55f);
        CHECK(sutRef.getTranslation() == sut.getTranslation());
    }

    SECTION("When stopped in the middle of the animation exactly half of translation change is done")
    {
        sutRef.moveTo(glm::vec3(1.5, 3.0, 9.0));
        sut.moveBy(2.2f, glm::vec3(2.0, 4.0, 12.0));
        sut.onTimePassed(1.1f);
        sut.onTimePassed(0.55f);
        CHECK(sutRef.getTranslation() == sut.getTranslation());
    }

    SECTION("Scale by one does not change anything in scale")
    {
        sut.scaleBy(1.1f, glm::vec3(1.0, 1.0, 1.0));
        sut.onTimePassed(1.0f);
        CHECK(glm::vec3(1.0, 1.0, 1.0) == sut.getScale());
    }

    SECTION("Scale by value different than one does change")
    {
        sut.scaleBy(1.1f, glm::vec3(1.0, 2.0, 3.0));
        sut.onTimePassed(1.0f);
        CHECK(glm::vec3(1.0, 0.0, 0.0) != sut.getScale());
    }

    SECTION("When scale change introduced and full time passed value become as requested")
    {
        sutRef.scaleTo(glm::vec3(2.0, 6.0, 11.0));
        sut.scaleBy(1.1f, glm::vec3(2.0, 6.0, 11.0));
        sut.onTimePassed(1.1f);
        CHECK(sutRef.getScale() == sut.getScale());
    }

    SECTION("When stopped in the middle of the animation exactly half of scale change is done")
    {
        sutRef.scaleTo(glm::vec3(0.75, 0.6, 1.5));
        sut.scaleBy(1.1f, glm::vec3(0.5, 0.2, 2.0));
        sut.onTimePassed(0.55f);
        CHECK(sutRef.getScale() == sut.getScale());
    }

    SECTION("Stopped in the middle of the animation and some time passed")
    {
        sutRef.scaleTo(glm::vec3(0.75, 0.6, 1.5));
        sut.scaleBy(1.1f, glm::vec3(0.5, 0.2, 2.0));
        sut.onTimePassed(0.55f);
        sut.stop();
        sut.onTimePassed(0.5f);
        CHECK(sutRef.getScale() == sut.getScale());
    }
}
