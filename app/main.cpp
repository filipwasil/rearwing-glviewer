
#include <cxxopts.hpp>

#include <Application.hpp>
#include <Logger.hpp>

#include <future>
#include <memory>
#include <string>
#include <thread>

int main(int argc, char* argv[])
{
  // todo parse options
  cxxopts::Options options(argv[0], "--- Options ---");

  // todo name the app for debugging purposes
  rwc::Logger logger{};

  try
  {
    auto parseResult = options.parse(argc, argv);
    auto app = std::make_unique<rwc::Application>();

    auto load_resources_fut = std::async(std::launch::async, [&app] {
      app->runBackgroundContext();
      rwc::log::info("start offscreen loop");
    });
    rwc::log::info("start onscreen loop");
    app->runRenderContext();
    app->runRenderLoop();
    rwc::log::info("stop render loop");
  }
  catch (...)
  {
    rwc::log::error("Exception");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

