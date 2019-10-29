#pragma once

#include <Context.hpp>

#include <array>
#include <tuple>

namespace rwc
{

/*!
 * @class UserContext
 *
 * @brief This class encapsulates user application details
 *        More specialized Context should inherit from this class and implment the interface
 *
 */
class GLContext : public Context
{
 public:
  GLContext();
  ~GLContext() override;

 private:
  void onPreloadResources() override;
  void onPreloadSceneGraph() override;
};

} // namespace rwc
