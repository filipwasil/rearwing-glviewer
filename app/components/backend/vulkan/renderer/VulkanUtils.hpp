#pragma once

#include "Vulkan.hpp"

namespace rwc
{

VKAPI_ATTR VkBool32 VKAPI_CALL MyDebugReportCallback(
  VkDebugReportFlagsEXT /*flags*/
  , VkDebugReportObjectTypeEXT /*objectType*/
  , uint64_t /*object*/
  , size_t /*location*/
  , int32_t /*messageCode*/
  , const char* /*layerPrefix*/
  , const char* /*message*/
  , void* /*userData*/);

} // namespace rwc
