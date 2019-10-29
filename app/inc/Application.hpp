#pragma once

#include <GLContext.hpp>

#include <memory>

namespace rwc
{

class Application final
{
 public:
  explicit Application();

  void runBackgroundContext();
  void runRenderContext();
  void runRenderLoop();
  void stopRenderLoop();

 private:
  void init(std::string mode);

  std::unique_ptr<GLContext> mScreen;
};

} // namespace rwc
