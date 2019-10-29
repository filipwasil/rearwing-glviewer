#pragma once

#include <map>
#include <string>
#include <vector>

#include "Uniform.hpp"
#include "RenderTag.hpp"

namespace rwc
{

/*!
 * @class Data oriented representation of OpenGL renderable object
 *
 */
struct RenderItem final
{
/*!
 * @brief render this renderItem
 *
 */
  void render() const;

/*!
 * @brief push Uniform with various types
 *
 */
  const RenderItem& useProgramObject() const;
  const RenderItem& pushUniform(const std::string& name, int data) const;
  const RenderItem& pushUniform(const std::string& name, int* data, int count) const;
  const RenderItem& pushUniform(const std::string& name, float data) const;
  const RenderItem& pushUniform(const std::string& name, float* data, int count) const;
  const RenderItem& pushUniform(const std::string& name, const glm::mat3& data) const;
  const RenderItem& pushUniform(const std::string& name, const glm::mat4& data) const;
  const RenderItem& pushUniform(const std::string& name, glm::mat4* data, int size) const;
  const RenderItem& pushUniform(const std::string& name, const glm::vec2& data) const;
  const RenderItem& pushUniform(const std::string& name, const glm::vec3& data) const;
  const RenderItem& pushUniform(const std::string& name, const vec3f& data) const;
  const RenderItem& pushUniform(const std::string& name, const vec2f& data) const;
  const RenderItem& pushUniform(const std::string& name, glm::vec3* data, int size) const;
  const RenderItem& pushUniform(const std::string& name, const glm::vec4& data) const;
  const RenderItem& pushUniform(const std::string& name, const vec4f& data) const;

/*!
 * @brief get tags assigned to this render item
 *
 */
  const std::vector<RenderTag>& getRenderTags() const
  {
    return mRenderTags;
  }

/*!
 * @struct OpenGL attribute data
 *
 */
  struct Attribute final
  {
    unsigned location{0};
    int count{0};
    unsigned type{0};
    int size{0};
    void* offset{nullptr};
    bool active{false};
  };

/*!
 * @struct OpenGL buffer object data
 *
 */
  struct Buffer final
  {
    int mElements{0};
    unsigned mName{0};
  };

/*!
 * @struct OpenGL buffer object data
 *
 */
  struct VertexArray final
  {
    bool mActive{false};
    unsigned mName{0};
  };

  /*!
* @struct OpenGL texture data
*
*/
  struct Texture final
  {
    unsigned mUnit{0};
    unsigned mName{0};
  };

  /*!
* @brief Vertex Buffer Object
*
*/
  Buffer mVBO{0};

/*!
 * @brief Index Buffer Object
 *
 */
  Buffer mIBO{0};

/*!
 * @brief Vertex Array Object
 *
 */
  VertexArray mVAO{false};

/*!
   * @brief Program Object
   *
   */
  unsigned mPO;

/*!
 * @brief Program Object
 *
 */
  unsigned mDrawType{0};

/*!
 * @brief Attributes
 *
 */
  std::vector<Attribute> mAttributes;

/*!
 * @brief Textures
 *
 */
  std::vector<Texture> mTextures;

/*!
 * @brief RenderTags
 *
 */
  std::vector<RenderTag> mRenderTags;

/*!
 * @brief Uniforms
 *
 */
  std::map<std::string, Uniform> mUniforms;
};

} // namespace rwc
