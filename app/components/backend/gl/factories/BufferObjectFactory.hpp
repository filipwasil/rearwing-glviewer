#pragma once

#include "../../RenderItem.hpp"
#include <Text.hpp>

namespace rwc
{

/*!
 * @class BufferObjectFactory
 *
 * @brief Loads an OpenGL Buffer Objects
 *
 */
class BufferObjectFactory
{
public:
    enum class Shape
    {
        rectangle
    };

/*!
 * @brief creates a RenderItem with predefined shape buffers
 *        Buffer contains only positions and texture coordinates
 *
 * @param shape id of the predefined buffer
 *
 */
    static RenderItem::Buffer create(Shape shape, const glm::mat4& transformation = glm::mat4{1.0f});

/*!
  * @brief Load a Full screen render item to fill the background
  *
  * @param[in] bufferToUpdate
  *
  * @param[in] pathFontMetadata path to vertex with program object texture atlas
  *
  * @param[in] text path to fragment with program object texture atlas
  *
  * @param[in] positionScreenSpace path to vertex with program object texture atlas
  *
  * @param[in] fontSize to fragment with program object texture atlas
  *
  * @param[in] screenResolution to fragment with program object texture atlas
  *
  * @return single render item
  *
  */
    static void updateTextBuffers(
        RenderItem::Buffer& buffer
        , const Text::Font& font
        , const std::string& text
        , const vec3f& position
        , float fontSize
        , const vec2f& screenResolution
        , Text::Alignment alignment = {Text::AlignmentHorizontal::left, Text::AlignmentVertical::bottom});

    static RenderItem::Buffer createTextBuffers(
        const char* pathFontMetadata
        , const std::string& text
        , const vec3f& position
        , float fontSize
        , const vec2f& screenResolution
        , Text::Alignment = {Text::AlignmentHorizontal::left, Text::AlignmentVertical::bottom});
};

} // namespace rwc
