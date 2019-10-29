#include <catch/catch.hpp>
#include <trompeloeil/trompeloeil.hpp>
#include <loader_textures_raw/stb_image.h>
#include <loader_textures_raw/TextureLoader.hpp>

using namespace rwc;
using trompeloeil::_;

stbi_uc* stbi_load(char const *filename, int *x, int *y, int *comp, int /*req_comp*/)
{
    if (std::string(filename) == "file_which_does_not_exist") {
        return nullptr;
    }
    *x = 1;
    *y = 1;
    *comp = false;
    return static_cast<stbi_uc*>(malloc(1));
}

TEST_CASE("loading textures from file", "[TextureLoader]")
{
    TextureLoader sut;
    SECTION("No texture should be loaded when a file does not exist")
    {
        unsigned int val = 0;
        REQUIRE_THROWS(val = sut.load("file_which_does_not_exist"));
        CHECK(0 == val);
    }

    SECTION("Valid texture should be loaded when a file does not exist")
    {
        CHECK(1 == sut.load("../models/test.png"));
    }
}

TEST_CASE("loading textures from generators", "[TextureLoader]")
{
    TextureLoader sut;
    SECTION("No program should be loaded when at least one shader file is missing")
    {
        CHECK(1 == sut.load("1_2_3.color"));
        CHECK(1 == sut.load("1_2_3.chessboard"));
    }
}
