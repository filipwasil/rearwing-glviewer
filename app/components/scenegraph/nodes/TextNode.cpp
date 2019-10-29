#include <nodes/TextNode.hpp>

#include <ConfigConstraints.hpp>
#include <FontFactory.hpp>
#include <RenderItemFactory.hpp>

namespace
{
    constexpr rwc::vec4f COLOR_WHITE{1.0, 1.0, 1.0, 1.0};
    constexpr rwc::vec4f COLOR_GREEN{0.533, 0.847, 0.978, 1.0};
    constexpr rwc::vec4f COLOR_RED{0.992, 0.486, 0.431, 1.0};

    // 3D Text creation algorithm uses size factor
    // instead of current resolution value
    constexpr float SIZE_FACTOR{1080.0f};
}

namespace rwc
{

TextNode::TextNode(
    const glm::mat4& viewProjectionMatrix
    , const char* text
    , const Text::Format& format
    , const char* vertexShaderPath
    , const char* fragmentShaderPath)
    : Node3D{RenderItemFactory::createTextRenderItem(
        format.fontMetadata
        , format.fontAtlas
        , vertexShaderPath
        , fragmentShaderPath
        , text
        , format.position
        , format.size
        , format.alignment
        , {SIZE_FACTOR, SIZE_FACTOR})}
    , mText{text}
    , mFontMetadata{format.fontMetadata}
    , mFontAtlas{format.fontAtlas}
    , mPosition{format.position}
    , mSize{format.size}
    , mFont(FontFactory::create(format.fontMetadata))
{
    mRenderItem.useProgramObject()
        .pushUniform("uColor", COLOR_WHITE)
        .pushUniform("uTextureUnit", DIFFUSE_TEXTURE_UNIT_UNIFORM)
        .pushUniform("uMVP", viewProjectionMatrix * mMMCGlobal);
}

TextNode::~TextNode() = default;

void TextNode::setText(const char* text)
{
    mText = text;
    recreateGPUBuffers();
}

void TextNode::setColor(const vec3f& color)
{
    mRenderItem.useProgramObject().pushUniform("uColor", color);
}

void TextNode::setSize(float size)
{
    mSize = size;
    recreateGPUBuffers();
}

void TextNode::setPosition(const vec3f& position)
{
    mPosition = position;
    recreateGPUBuffers();
}

void TextNode::recreateGPUBuffers()
{
    BufferObjectFactory::updateTextBuffers(mRenderItem.mVBO, mFont, mText, mPosition, mSize, {SIZE_FACTOR, SIZE_FACTOR});
}

} // namespace rwc
