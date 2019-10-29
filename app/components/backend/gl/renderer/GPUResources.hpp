#pragma once

#include "../../RenderItem.hpp"

#include <vector>

namespace rwc
{

struct RenderItem;

/*!
 * @struct Represents all GPU resources possible to be used by render item
 *
 */
struct GPUResources final
{
    std::vector<unsigned> buffers;
    std::vector<unsigned> programs;
    std::vector<unsigned> vertexArrays;
    std::vector<unsigned> textures;

    ~GPUResources();

/*!
* @brief Get unique GPU objects which belong to render item passed as argument
*
* @param [in] renderItem single render item used by renderer
*/
    template <typename TRenderItem>
    inline void collectUniqueResources(const TRenderItem& renderItem)
    {
        if (0 != renderItem.mVBO.mName)
        {
            buffers.push_back(renderItem.mVBO.mName);
        }
        if (0 != renderItem.mIBO.mName)
        {
            buffers.push_back(renderItem.mIBO.mName);
        }
        if (0 != renderItem.mPO)
        {
            programs.push_back(renderItem.mPO);
        }
        if (0 != renderItem.mVAO.mName)
        {
            vertexArrays.push_back(renderItem.mVAO.mName);
        }
        for (const auto texture : renderItem.mTextures)
        {
            textures.push_back(texture.mName);
        }
    }
};

} // namespace rwc