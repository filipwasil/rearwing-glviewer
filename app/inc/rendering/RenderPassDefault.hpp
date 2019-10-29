#pragma once

#include <array>
#include <Math.hpp>

namespace rwc
{

/*!
 * @class RenderPassDefault is a default class to be used together with renderer.
 *        Its purpose is to implement preRender and postRender callbacks.
 *        It is used as first parameter for Renderer class specialization.
 */
struct RenderPassDefault final
{
/*
 * @brief called by renderer before render items starts to render
 */
  void preRender();

/*
 * @brief called by renderer after render items starts to render
 */
  void postRender();
};

} // namespace rwc
