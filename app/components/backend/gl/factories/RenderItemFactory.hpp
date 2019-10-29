#pragma once

#include "BufferObjectFactory.hpp"
#include <Text.hpp>
#include "../../RenderItem.hpp"
#include <array>
#include <vector>

namespace rwc
{

class RenderItem;

/*!
 * @brief Load an asset choosing from predefined buffers called Shapes
 *
 * @param shape one of predefine geometry types
 *
 * @param pathFragmentShader path to vertex shader source file
 *
 * @param pathFragmentShader path to fragment shader source file
 *
 * @param pathTexture path to diffuse texture
 *
 */
class RenderItemFactory
{
public:

    static RenderItem create(
        BufferObjectFactory::Shape shape
        , const char* pathVertexShader
        , const char* pathFragmentShader
        , const char* pathTexture
        , const glm::mat4& transformation);

/*!
 * @brief Load an asset choosing from predefined buffers called Shapes
 *
 * @param shape one of predefine geometry types
 *
 * @param pathProgramBinary path to binary program object file
 *
 * @param pathTexture path to diffuse texture
 *
 */
    static RenderItem create(
        BufferObjectFactory::Shape shape
        , const char* pathProgramBinary
        , const char* pathTexture
        , const glm::mat4& transformation);

/*!
 * @brief Load an asset and initialize all related buffers
 *
 * @param[in] pathModel path to obj file containing the buffers
 *
 * @param[in] pathVertexShader path to file containg vertex shader code
 *
 * @param[in] pathFragmentShader path to file containing fragment shader code
 *
 * @param[in] pathTexture path to image which will be used as a texture
 *
 * @return vector of initialzied Node3Ds
 *
 */
    static std::vector<RenderItem> create(
        const char* pathModel
        , const char* pathVertexShader
        , const char* pathFragmentShader
        , const char* pathTexture);

/*!
 * @brief Load an asset and initialize all related buffers
 *
 * @param[in] pathModel path to obj file containing the buffers
 *
 * @param[in] pathProgramcBinary path to file containg program object binary
 *
 * @param[in] pathTexture path to image which will be used as a texture
 *
 * @return vector of RenderItems
 *
 */
    static std::vector<RenderItem> create(
        const char* path
        , const char* pathProgramcBinary
        , const char* pathTexture);

/*!
 * @brief Load a TextRenderItem
 *
 * @param[in] pathFontMetadata path to font metadata
 *
 * @param[in] pathFontAtlas path to font texture atlas
 *
 * @param[in] pathToProgramBinary path to binary with program object texture atlas
 *
 * @param[in] text content which will be rendered
 *
 * @param[in] positionScreenSpace position in screen space x(-1.0, 1.0), y(-1.0, 1.0)
 *
 * @param[in] fontSize size of font in pixels
 *
 * @param[in] screenResolution resolution of the screen in (width, height) format
 *
 * @return RenderItem
 *
 */
    static RenderItem createTextRenderItem(
        const char* pathFontMetadata
        , const char* pathFontAtlas
        , const char* pathToProgramBinary
        , const std::string& text
        , const vec3f& positionScreenSpace = {0.0, 0.0, 0.0}
        , float fontSize = 100.0f
        , Text::Alignment alignment = {Text::AlignmentHorizontal::left, Text::AlignmentVertical::bottom}
        , const vec2f& screenResolution = {1920.0, 1080.0});


/*!
  * @brief Load a TextRenderItem
  *
  * @param[in] pathFontMetadata path to font metadata
  *
  * @param[in] pathFontAtlas path to font texture atlas
  *
  * @param[in] pathToVertexShader path to vertex with program object texture atlas
  *
  * @param[in] pathToFragmentShader path to fragment with program object texture atlas
  *
  * @param[in] text content which will be rendered
  *
  * @param[in] positionScreenSpace position in screen space x(-1.0, 1.0), y(-1.0, 1.0)
  *
  * @param[in] fontSize size of font in pixels
  *
  * @param[in] screenResolution resolution of the screen in (width, height) format
  *
  * @return RenderItem
  *
  */
    static RenderItem createTextRenderItem(
        const char* pathFontMetadata
        , const char* pathFontAtlas
        , const char* pathToVertexShader
        , const char* pathToFragmentShader
        , const std::string& text
        , const vec3f& positionScreenSpace = {0.0, 0.0, 0.0}
        , float fontSize = 100.0f
        , Text::Alignment alignment = {Text::AlignmentHorizontal::left, Text::AlignmentVertical::bottom}
        , const vec2f& screenResolution = {1920.0, 1080.0});

/*!
  * @brief Load a Full screen render item to fill the background
  *
  * @param[in] pathToProgramBinary path to program binary
  *
  * @return single render item
  *
  */
    static RenderItem createBackgroundRenderItem(const char* pathToProgramBinary);

/*!
  * @brief Load a Full screen render item to fill the background
  *
  * @param[in] pathToVertexShader path to vertex with program object texture atlas
  *
  * @param[in] pathToFragmentShader path to fragment with program object texture atlas
  *
  * @return single render item
  *
  */
    static RenderItem createBackgroundRenderItem(const char* pathToVertexShader, const char* pathToFragmentShader);

private:

    static std::vector<RenderItem> create(const char* path, unsigned programId);

    static void validateAttributes(RenderItem& renderItem);
    static void initActiveUniforms(RenderItem& renderItem);
};

} // namespace rwc
