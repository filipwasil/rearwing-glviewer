#include <widgets/TextWidget.hpp>

#include <ConfigConstraints.hpp>
#include <FontFactory.hpp>
#include <RenderItemFactory.hpp>

namespace
{
    constexpr rwc::vec4f COLOR_WHITE{1.0, 1.0, 1.0, 1.0};
    constexpr rwc::vec4f COLOR_GREEN{0.533, 0.847, 0.978, 1.0};
    constexpr rwc::vec4f COLOR_RED{0.992, 0.486, 0.431, 1.0};
}

namespace rwc
{

TextWidget::TextWidget(const char* text, const Text::Format& format, const vec2f& resolution)
    : mText{text}
    , mFontMetadata{format.fontMetadata}
    , mFontAtlas{format.fontAtlas}
    , mPosition{format.position[0], format.position[1]}
    , mResolution{resolution}
    , mSize{format.size}
    , mFont(FontFactory::create(format.fontMetadata))
    , mAlignment(format.alignment)
    , mRenderItem{RenderItemFactory::createTextRenderItem(
        format.fontMetadata
        , format.fontAtlas
        , "shaders/Text.vert"
        , "shaders/Text.frag"
        , text
        , format.position
        , format.size
        , format.alignment
        , mResolution)}
{
    mRenderItem.useProgramObject()
        .pushUniform("uColor", COLOR_WHITE)
        .pushUniform("uTextureUnit", DIFFUSE_TEXTURE_UNIT_UNIFORM)
        .pushUniform("uMVP", glm::mat4(1.0));
}

TextWidget::~TextWidget() = default;

const RenderItem& TextWidget::getRenderItem() const
{
    return mRenderItem;
}

void TextWidget::setText(const char* text)
{
    mText = text;
    recreateGPUBuffers();
}

void TextWidget::setColor(const vec3f& color)
{
    mRenderItem.useProgramObject().pushUniform("uColor", color);
}

void TextWidget::setSize(float size)
{
    mSize = size;
    recreateGPUBuffers();
}

void TextWidget::setPosition(const vec2f& position)
{
    mPosition = position;
    recreateGPUBuffers();
}

void TextWidget::recreateGPUBuffers()
{
    BufferObjectFactory::updateTextBuffers(mRenderItem.mVBO, mFont, mText, {mPosition[0], mPosition[1], 0.0f}, mSize, mResolution);
}

} // namespace rwc
