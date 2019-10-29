#pragma once

#include "Vulkan.hpp"
#include <window/Window.hpp>
#include <vector>

namespace rwc {

class Platform final {
 public:
  Platform (const char* name, Window& window);

  const VkPhysicalDevice& getPhysicalDevice() const;
  const VkSurfaceFormatKHR& getSurfaceFormat() const;
  const VkSurfaceCapabilitiesKHR getSurfaceCapabilities() const;
  const VkSurfaceKHR& getSurface() const;
  unsigned int getQueueFamily() const;

  VkDevice& getDevice();
  VkInstance& getInstance();
  uint32_t getFirstValidMemoryTypeIdx(uint32_t type, VkFlags requirements);

 private:
  void initPhysicalDevices();
  void initPhysicalDevice();
  void initLogicalDevice();

 private:
  struct PhysicalDevices {
    std::vector<VkPhysicalDevice> mDevices;
    std::vector<VkPhysicalDeviceProperties> mDeviceProperties;
    std::vector<VkPhysicalDeviceMemoryProperties> mDeviceMemoryProperties;
    std::vector< std::vector<VkQueueFamilyProperties> > mQueueFamilyProps;
    std::vector< std::vector<VkBool32> > mQueueSupportPresent;
    std::vector< std::vector<VkSurfaceFormatKHR> > mSurfaceFormats;
    std::vector<VkSurfaceCapabilitiesKHR> mSurfaceCapabilities;
  };

 private:
  VkInstance mInstance;
  VkDevice mDevice;
  VkSurfaceKHR mSurface;
  PhysicalDevices mPhysicalDevices;
  unsigned int mGraphicsDeviceIndex;
  unsigned int mGraphicsDeviceQueueFamily;
};

} // namespace rwc
