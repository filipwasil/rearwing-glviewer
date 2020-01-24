#pragma once

#define SPDLOG_INCLUDE_START                                                 \
    _Pragma("GCC diagnostic push")                                           \
    _Pragma("GCC diagnostic ignored \"-Wstrict-overflow\"")                  \
    _Pragma("GCC diagnostic ignored \"-Wshadow\"")                           \
    _Pragma("GCC diagnostic ignored \"-Wsign-promo\"")                       \
    _Pragma("GCC diagnostic ignored \"-Wredundant-move\"")

#define SPDLOG_INCLUDE_END                                                   \
    _Pragma("GCC diagnostic pop")


SPDLOG_INCLUDE_START
#define SPDLOG_FMT_EXTERNAL

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/async.h>

namespace rwc
{

namespace log = ::spdlog;

class Logger final
{
 public:
  using Level = ::spdlog::level::level_enum;
  Logger(Level debugLevel = ::spdlog::level::debug)
    : level{debugLevel}
    , oveflowPolicy{::spdlog::async_overflow_policy::block}
  {
    ::spdlog::init_thread_pool(4096, 1);
    auto logger = std::make_shared<::spdlog::async_logger>(
      "Rearwing application"
      , std::make_shared<::spdlog::sinks::stdout_color_sink_mt>()
      , ::spdlog::thread_pool()
      , oveflowPolicy);
    logger->set_level(level);
    ::spdlog::register_logger(logger);
    ::spdlog::set_default_logger(logger);
  }

 private:
  ::spdlog::level::level_enum level;
  ::spdlog::async_overflow_policy oveflowPolicy;
};

} // namespace rwc
SPDLOG_INCLUDE_END
