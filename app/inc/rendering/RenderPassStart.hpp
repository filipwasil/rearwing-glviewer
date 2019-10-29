#pragma once

#include <array>

namespace rwc
{

/*!
 * @class RenderPassDefault is a default class to be used together with renderer.
 *        Its purpose is to implement preRender and postRender callbacks.
 *        It is used as first parameter for Renderer class specialization.
 */
struct RenderPassStart final
{
/*
 * @brief called by renderer before render items starts to render
 */
  void preRender();

/*
 * @brief called by renderer after render items starts to render
 */
  void postRender();

 private:
  std::array<int, 3> mBlending{-1};
  std::array<int, 3> mDepth{-1};
  std::array<int, 3> mStencil{-1};
  std::array<int, 3> mRenderTarget{-1};
};

} // namespace rwc
