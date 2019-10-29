#include <nodes/Plane3D.hpp>

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

Plane3D::Plane3D(
    const glm::mat4& viewProjectionMatrix
    , const glm::mat4& transformation
    , const char* vertexShaderPath
    , const char* fragmentShaderPath
    , const char* texturePath)
    : Node3D(
    RenderItemFactory::create(BufferObjectFactory::Shape::rectangle
        , vertexShaderPath
        , fragmentShaderPath
        , texturePath
        , transformation))
{
    mRenderItem.useProgramObject()
        .pushUniform("uSamplerDiffuse", DIFFUSE_TEXTURE_UNIT_UNIFORM)
        .pushUniform("uMVP", viewProjectionMatrix * mMMCGlobal);
}

Plane3D::Plane3D(
  const glm::mat4& viewProjectionMatrix
  , const glm::mat4& transformation
  , const char* binaryShaderPath
  , const char* texturePath)
  : Node3D(
  RenderItemFactory::create(BufferObjectFactory::Shape::rectangle
    , binaryShaderPath
    , texturePath
    , transformation))
{
  mRenderItem.useProgramObject()
    .pushUniform("uSamplerDiffuse", DIFFUSE_TEXTURE_UNIT_UNIFORM)
    .pushUniform("uMVP", viewProjectionMatrix * mMMCGlobal);
}

Plane3D::~Plane3D() = default;

} // namespace rwc
