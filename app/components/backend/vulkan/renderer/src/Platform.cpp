#include <Platform.hpp>
#include <Log.hpp>
#include <VulkanUtils.hpp>
#include <array>
#include <cassert>
#include <limits>

namespace rwc {

PFN_vkCreateDebugReportCallbackEXT my_vkCreateDebugReportCallbackEXT = nullptr;

Platform::Platform(const char* appName, Window& window)
  : mInstance {}
  , mDevice {}
  , mSurface {}
  , mPhysicalDevices {}
  , mGraphicsDeviceIndex (std::numeric_limits<unsigned int>::max())
  , mGraphicsDeviceQueueFamily (std::numeric_limits<unsigned int>::max()) {

  std::vector<VkExtensionProperties> ExtProps;

  // Initializing extensions
  uint NumExt = 0;
  logC("vkEnumerateInstanceExtensionProperties error",
       vkEnumerateInstanceExtensionProperties(nullptr, &NumExt, nullptr));

  printf("Found %d extensions\n", NumExt);

  ExtProps.resize(NumExt);

  logC("vkEnumerateInstanceExtensionProperties error",
        vkEnumerateInstanceExtensionProperties(nullptr, &NumExt, &ExtProps[0]));


  for (uint i = 0 ; i < NumExt ; i++) {
    printf("Instance extension %d - %s\n", i, ExtProps[i].extensionName);
  }
  //

  // Create the instance
  VkApplicationInfo appInfo = {};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = appName;
  appInfo.engineVersion = 1;
  appInfo.apiVersion = VK_API_VERSION_1_0;

#ifdef ENABLE_DEBUG_LAYERS
  std::array<const char*, 1> pInstLayers[] = {
    "VK_LAYER_LUNARG_standard_validation"
  };
#endif

  auto extensions = window.getExtensions();
  VkInstanceCreateInfo instInfo = {};
  instInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instInfo.pApplicationInfo = &appInfo;

#ifdef ENABLE_DEBUG_LAYERS
  instInfo.enabledLayerCount = pInstLayers->size();
  instInfo.ppEnabledLayerNames = pInstLayers->data();
#endif

  instInfo.enabledExtensionCount = extensions.size();
  instInfo.ppEnabledExtensionNames = extensions.data();

  logC("vkCreateInstance", vkCreateInstance(&instInfo, nullptr, &mInstance));

#ifdef ENABLE_DEBUG_LAYERS
  // Get the address to the vkCreateDebugReportCallbackEXT function
    my_vkCreateDebugReportCallbackEXT =
      reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(vkGetInstanceProcAddr(
        mInstance, "vkCreateDebugReportCallbackEXT"));

    // Register the debug callback
    VkDebugReportCallbackCreateInfoEXT callbackCreateInfo;
    callbackCreateInfo.sType       = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
    callbackCreateInfo.pNext       = nullptr;
    callbackCreateInfo.flags       = VK_DEBUG_REPORT_ERROR_BIT_EXT |
                                     VK_DEBUG_REPORT_WARNING_BIT_EXT |
                                     VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
    callbackCreateInfo.pfnCallback = &MyDebugReportCallback;
    callbackCreateInfo.pUserData   = nullptr;

    VkDebugReportCallbackEXT callback;
    logC("my_vkCreateDebugReportCallbackEXT error"
         , my_vkCreateDebugReportCallbackEXT(mInstance, &callbackCreateInfo, nullptr, &callback));
#endif

#ifdef WIN32
  assert(0);
#else
  mSurface = window.createSurface(mInstance);
#endif
  printf("Surface created\n");

  initPhysicalDevices();
  initPhysicalDevice();
  initLogicalDevice();
}

void Platform::initPhysicalDevices() {
  uint32_t devicesCount = 0;

  VkResult res = vkEnumeratePhysicalDevices(mInstance, &devicesCount, nullptr);
  logC("vkEnumeratePhysicalDevices error ", res);

  printf("Num physical devices %d\n", devicesCount);

  mPhysicalDevices.mDevices.resize(devicesCount);
  mPhysicalDevices.mDeviceProperties.resize(devicesCount);
  mPhysicalDevices.mDeviceMemoryProperties.resize(devicesCount);
  mPhysicalDevices.mQueueFamilyProps.resize(devicesCount);
  mPhysicalDevices.mQueueSupportPresent.resize(devicesCount);
  mPhysicalDevices.mSurfaceFormats.resize(devicesCount);
  mPhysicalDevices.mSurfaceCapabilities.resize(devicesCount);

  res = vkEnumeratePhysicalDevices(mInstance, &devicesCount, &mPhysicalDevices.mDevices[0]);
  logC("vkEnumeratePhysicalDevices", res);

  for (uint i = 0 ; i < devicesCount ; i++) {
    const VkPhysicalDevice& dev = mPhysicalDevices.mDevices[i];
    vkGetPhysicalDeviceProperties(dev, &mPhysicalDevices.mDeviceProperties[i]);
    vkGetPhysicalDeviceMemoryProperties(mPhysicalDevices.mDevices[i], &mPhysicalDevices.mDeviceMemoryProperties[i]);
    printf("Device name: %s\n", mPhysicalDevices.mDeviceProperties[i].deviceName);
    uint32_t apiVer = mPhysicalDevices.mDeviceProperties[i].apiVersion;
    printf("    API version: %d.%d.%d\n", VK_VERSION_MAJOR(apiVer), VK_VERSION_MINOR(apiVer), VK_VERSION_PATCH(apiVer));
    uint NumQFamily = 0;

    vkGetPhysicalDeviceQueueFamilyProperties(dev, &NumQFamily, nullptr);

    printf("    Num of family queues: %d\n", NumQFamily);

    mPhysicalDevices.mQueueFamilyProps[i].resize(NumQFamily);
    mPhysicalDevices.mQueueSupportPresent[i].resize(NumQFamily);

    vkGetPhysicalDeviceQueueFamilyProperties(dev, &NumQFamily, &(mPhysicalDevices.mQueueFamilyProps[i][0]));

    for (uint q = 0; q < NumQFamily; q++) {
      res = vkGetPhysicalDeviceSurfaceSupportKHR(dev, q, mSurface, &(mPhysicalDevices.mQueueSupportPresent[i][q]));
      logC("vkGetPhysicalDeviceSurfaceSupportKHR error ", res);
    }

    unsigned int numFormats = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(dev, mSurface, &numFormats, nullptr);
    assert(numFormats > 0);

    mPhysicalDevices.mSurfaceFormats[i].resize(numFormats);

    res = vkGetPhysicalDeviceSurfaceFormatsKHR(dev, mSurface, &numFormats, &(mPhysicalDevices.mSurfaceFormats[i][0]));
    logC("vkGetPhysicalDeviceSurfaceFormatsKHR error ", res);

    for (unsigned int j = 0 ; j < numFormats ; ++j) {
      const VkSurfaceFormatKHR& SurfaceFormat = mPhysicalDevices.mSurfaceFormats[i][j];
      printf("    Format %d color space %d\n", SurfaceFormat.format , SurfaceFormat.colorSpace);
    }

    res = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(dev, mSurface, &(mPhysicalDevices.mSurfaceCapabilities[i]));
    logC("vkGetPhysicalDeviceSurfaceCapabilitiesKHR error ", res);

    logImageUsageFlags(mPhysicalDevices.mSurfaceCapabilities[i].supportedUsageFlags);

    uint NumPresentModes = 0;

    res = vkGetPhysicalDeviceSurfacePresentModesKHR(dev, mSurface, &NumPresentModes, nullptr);
    logC("vkGetPhysicalDeviceSurfacePresentModesKHR error ", res);

    assert(NumPresentModes != 0);

    printf("Number of presentation modes %d\n", NumPresentModes);
  }
}

void Platform::initPhysicalDevice() {
  auto countDevices = mPhysicalDevices.mDevices.size();
  for (decltype(countDevices) i = 0; i < countDevices; ++i) {
    auto countDeviceQueueFamilyProperties = mPhysicalDevices.mQueueFamilyProps[i].size();
    for (decltype(countDeviceQueueFamilyProperties) j = 0; j < countDeviceQueueFamilyProperties; ++j) {
      VkQueueFamilyProperties& QFamilyProp = mPhysicalDevices.mQueueFamilyProps[i][j];

      printf("Family %lu Num queues: %d\n", j, QFamilyProp.queueCount);
      VkQueueFlags flags = QFamilyProp.queueFlags;
      printf("    GFX %s, Compute %s, Transfer %s, Sparse binding %s\n",
             (flags & VK_QUEUE_GRAPHICS_BIT) ? "Yes" : "No",
             (flags & VK_QUEUE_COMPUTE_BIT) ? "Yes" : "No",
             (flags & VK_QUEUE_TRANSFER_BIT) ? "Yes" : "No",
             (flags & VK_QUEUE_SPARSE_BINDING_BIT) ? "Yes" : "No");

      if ((flags & VK_QUEUE_GRAPHICS_BIT) && (mGraphicsDeviceIndex == std::numeric_limits<unsigned int>::max())) {
        if (!mPhysicalDevices.mQueueSupportPresent[i][j]) {
          printf("Present is not supported\n");
          continue;
        }

        mGraphicsDeviceIndex = i;
        mGraphicsDeviceQueueFamily = j;
        printf("Using GFX device %d and queue family %d\n", mGraphicsDeviceIndex, mGraphicsDeviceQueueFamily);
      }
    }
  }

  if (mGraphicsDeviceIndex == std::numeric_limits<unsigned int>::max()) {
    printf("No GFX device found!\n");
    assert(0);
  }
}

void Platform::initLogicalDevice() {
  VkDeviceQueueCreateInfo qInfo = {};
  qInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;

  float qPriorities = 1.0f;
  qInfo.queueCount = 1;
  qInfo.pQueuePriorities = &qPriorities;
  qInfo.queueFamilyIndex = mGraphicsDeviceQueueFamily;

  std::array<const char*, 1> extensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
  };

  VkDeviceCreateInfo devInfo = {};
  devInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  devInfo.enabledExtensionCount = extensions.size();
  devInfo.ppEnabledExtensionNames = extensions.data();
  devInfo.queueCreateInfoCount = 1;
  devInfo.pQueueCreateInfos = &qInfo;

  VkResult res = vkCreateDevice(getPhysicalDevice(), &devInfo, nullptr, &mDevice);

  logC("vkCreateDevice error ", res);

  printf("Device created\n");
}

uint32_t Platform::getFirstValidMemoryTypeIdx(uint32_t typeBits, VkFlags requirements) {
  // Search memtypes to find first index with those properties
  for (uint32_t i = 0; i < mPhysicalDevices.mDeviceMemoryProperties[mGraphicsDeviceIndex].memoryTypeCount; i++) {
    if ((typeBits & 1) == 1) {
      // Type is available, does it match user properties?
      if ((mPhysicalDevices.mDeviceMemoryProperties[mGraphicsDeviceIndex].memoryTypes[i].propertyFlags & requirements)
          == requirements) {
        return i;
      }
    }
    typeBits >>= 1;
  }
  logF("No memory types matched ");
  return 0;
}

const VkPhysicalDevice& Platform::getPhysicalDevice() const {
  return mPhysicalDevices.mDevices[mGraphicsDeviceIndex];
}

const VkSurfaceFormatKHR& Platform::getSurfaceFormat() const {
  return mPhysicalDevices.mSurfaceFormats[mGraphicsDeviceIndex][0];
}

const VkSurfaceCapabilitiesKHR Platform::getSurfaceCapabilities() const {
  return mPhysicalDevices.mSurfaceCapabilities[mGraphicsDeviceIndex];
}

const VkSurfaceKHR& Platform::getSurface() const {
  return mSurface;
}

unsigned int Platform::getQueueFamily() const {
  return mGraphicsDeviceQueueFamily;
}

VkDevice& Platform::getDevice() {
  return mDevice;
}

VkInstance& Platform::getInstance() {
  return mInstance;
}

} // namespace rwc