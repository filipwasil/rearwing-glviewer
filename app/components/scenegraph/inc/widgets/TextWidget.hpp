#pragma once

#include <FontFactory.hpp>
#include "../../../backend/RenderItem.hpp"

namespace rwc
{

class TextWidget
{
public:
    TextWidget(const char* text, const Text::Format& format, const vec2f& resolution);

    virtual ~TextWidget();

    void setText(const char* text);
    void setColor(const vec3f& color);
    void setSize(float size);
    void setPosition(const vec2f& size);

    const RenderItem& getRenderItem() const;

private:
    void recreateGPUBuffers();

    std::string mText;
    std::string mFontMetadata;
    std::string mFontAtlas;
    vec2f mPosition;
    vec2f mResolution;
    float mSize;
    Text::Font mFont;
    Text::Alignment mAlignment;
    RenderItem mRenderItem;
};

} // namespace rwc