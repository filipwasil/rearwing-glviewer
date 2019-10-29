#pragma once

#include <FontFactory.hpp>
#include <nodes/Node3D.hpp>

namespace rwc
{

class TextNode : public Node3D
{
public:
    TextNode(
        const glm::mat4& viewProjectionMatrix
        , const char* text
        , const Text::Format& format
        , const char* vertexShaderPath = "shaders/Text.vert"
        , const char* fragmentShaderPath = "shaders/Text.frag");

    ~TextNode() override;

    void setText(const char* text);
    void setColor(const vec3f& color);
    void setSize(float size);
    void setPosition(const vec3f& size);

private:
    void recreateGPUBuffers();

    std::string mText;
    std::string mFontMetadata;
    std::string mFontAtlas;
    vec3f mPosition;
    float mSize;
    Text::Font mFont;
};

} // namespace rwc