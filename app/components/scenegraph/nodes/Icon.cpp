#include <nodes/Icon.hpp>

#include <ConfigConstraints.hpp>
#include <RenderItemFactory.hpp>

namespace
{
    constexpr rwc::vec4f COLOR_WHITE{1.0, 1.0, 1.0, 1.0};
    constexpr rwc::vec4f COLOR_GREEN{0.533, 0.847, 0.978, 1.0};
    constexpr rwc::vec4f COLOR_RED{0.992, 0.486, 0.431, 1.0};
}

namespace rwc
{

Icon::Icon(const glm::mat4& viewProjectionMatrix, const char* iconPath, const glm::mat4& transformation)
    : Plane3D(viewProjectionMatrix, transformation, "shaders/BasicNoNormals.vert", "shaders/TextureColored.frag", iconPath)
{
    mRenderItem.useProgramObject()
        .pushUniform("uSamplerDiffuse", DIFFUSE_TEXTURE_UNIT_UNIFORM)
        .pushUniform("uColor", COLOR_WHITE)
        .pushUniform("uMVP", viewProjectionMatrix * mMMCGlobal);
}

Icon::~Icon() = default;

void Icon::setActive(bool active)
{
    mRenderItem.useProgramObject().pushUniform("uColor", active ? COLOR_WHITE : COLOR_RED);
}

} // namespace rwc
