#pragma once

#include "gl/renderer/GPUResources.hpp"

#include <functional>
#include <tuple>
#include <vector>

namespace rwc
{

/*!
 * @class Renderer
 *
 * @brief Encapsulates the rendering pipeline, keeps the render items
 *        Controls the relation between RenderItems and RenderPasses
 *
 */
template <typename TRenderItem, typename ...TRenderPasses>
class Renderer final
{
 private:
/*!
 * @struct IndexHelper
 *
 * @brief Usable when want to get the type index from the tuple
 *
 */
  template <class T, class Tuple>
  struct IndexHelper
  {
    static const std::size_t value = 0;
    static_assert("a");
  };

  template <class T, class... Types>
  struct IndexHelper<T, std::tuple<T, Types...>>
  {
    static const std::size_t value = 0;
  };

  template <class T, class U, class... Types>
  struct IndexHelper<T, std::tuple<U, Types...>>
  {
    static const std::size_t value = 1 + IndexHelper<T, std::tuple<Types...>>::value;
  };

  using RenderPasses = std::tuple<TRenderPasses...>;
  static constexpr size_t RenderPassesCount{sizeof...(TRenderPasses)};

 public:
  Renderer() = default;

/*!
 * @brief Flush the current rendering pipeline
 *
 */
  void render()
  {
    renderRenderItems();
  }

/*!
 * @brief Add the render items to rendering pipeline under specific render pass
 *
 * @param renderItems vector of render items ready to be rendered
 *
 */
  template <typename TRenderPass>
  void addToRenderingPipeline(const std::vector<TRenderItem>& renderItems)
  {
    constexpr size_t idx = IndexHelper<TRenderPass, RenderPasses>::value;
    mRenderItems[idx].insert(mRenderItems[idx].end(), renderItems.begin(), renderItems.end());
    for (const auto& renderItem : renderItems)
    {
      if constexpr (std::is_pointer<TRenderItem>::value)
      {
        mGPUResources.collectUniqueResources(*renderItem);
      }
      else
      {
        mGPUResources.collectUniqueResources(renderItem);
      }
    }
  }

/*!
 * @brief Add the render items to rendering pipeline under specific render pass
 *
 * @param renderItems vector of render items ready to be rendered
 *
 */
  template <typename TRenderPass>
  void addToRenderingPipeline(const TRenderItem& renderItem)
  {
    constexpr size_t idx = IndexHelper<TRenderPass, RenderPasses>::value;
    mRenderItems[idx].push_back(renderItem);
    if constexpr (std::is_pointer<TRenderItem>::value)
    {
      mGPUResources.collectUniqueResources(*renderItem);
    }
    else
    {
      mGPUResources.collectUniqueResources(renderItem);
    }
  }

/*!
 * @brief Clear all render passes and render items in this renderer
 *
 */
  void clearRenderingPipeline()
  {
    for (auto& renderItem : mRenderItems)
    {
      renderItem.clear();
    }
  }

/*!
 * @brief Clear all render items for one renderpass
 *
 */
  template <typename TRenderPass>
  void clearRenderPass()
  {
    constexpr size_t idx = IndexHelper<TRenderPass, RenderPasses>::value;
    mRenderItems[idx].clear();
  }

/*!
 * @brief Updates vertex buffer object
 *
 * @tparam TRenderPass render pass used to narrow the search
 *
 * @param buffer contains the valid state of vertex buffer object according to which
 *        the render item in renderer will be updated
 *
 */
  template <typename TRenderPass>
  void updateVBO(const TRenderItem& renderItem)
  {
    constexpr size_t idx = IndexHelper<TRenderPass, RenderPasses>::value;
    for (auto& renderItemToUpdate : mRenderItems[idx])
    {
      if (renderItemToUpdate.mVBO.mName == renderItem.mVBO.mName)
      {
        renderItemToUpdate.mVBO = renderItem.mVBO;
        return;
      }
    }
  }

/*!
 * @brief Perform an action over a tagged renderItems
 *
 * @tparam TRenderPass render pass used to narrow the search
 *
 * @param action will be executed within
 *
 */
  template <typename TRenderPass>
  void populateTagged(RenderTag tag, std::function<void(RenderItem&)> action)
  {
    const std::vector<RenderItem>& items = mRenderItems[IndexHelper<TRenderPass, RenderPasses>::value];

    std::for_each(items.begin(), items.end(), [tag, action] (RenderItem& ri)
    {
      const std::vector<RenderTag>& tags = ri.getRenderTags();
      if (std::any_of(tags.begin(), tags.end(), [tag, action](const RenderTag& rt){ return rt == tag; }))
      {
        action(ri);
      }
    });
  }

 private:
  template <size_t TIndex = 0>
  constexpr void renderRenderItems()
  {
    if constexpr (TIndex < RenderPassesCount)
    {
      std::get<TIndex>(mRenderPasses).preRender();
      for (auto renderItem : mRenderItems[TIndex])
      {
        if constexpr (std::is_pointer<TRenderItem>::value)
        {
          renderItem->render();
        }
        else
        {
          renderItem.render();
        }
      }
      std::get<TIndex>(mRenderPasses).postRender();
      renderRenderItems<TIndex + 1>();
    }
  }

  RenderPasses mRenderPasses{};
  GPUResources mGPUResources{};
  std::array<std::vector<TRenderItem>, RenderPassesCount> mRenderItems{};
};

} // namespace rwc
