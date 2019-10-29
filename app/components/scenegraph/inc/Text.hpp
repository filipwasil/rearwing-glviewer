#pragma once

#include <Math.hpp>

namespace rwc
{

struct Text
{
    enum class AlignmentHorizontal
    {
        left
        , right
        , center
    };

    enum class AlignmentVertical
    {
        top
        , bottom
        , center
    };

    struct Alignment
    {
        AlignmentHorizontal horizontal;
        AlignmentVertical vertical;
    };

    struct Font
    {
        float offsets[256]{0.0f};
        float widths[256]{0.0f};
        int atlasColumns{16};
        int atlasRows{16};
    };

    struct Format
    {
        const vec3f position;
        float size;
        const char* fontMetadata;
        const char* fontAtlas;
        Alignment alignment{AlignmentHorizontal::left, AlignmentVertical::bottom};
    };
};



} // namespace rwc

