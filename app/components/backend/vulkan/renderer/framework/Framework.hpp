#pragma once

#include <Platform.hpp>
#include <core/VertexBuffer.hpp>
#include <core/UniformBuffer.hpp>
#include <core/StagingBuffer.hpp>
#include <core/Texture.hpp>

namespace rwc {

class Framework {
 public:
  Framework(const char* appName, unsigned int width, unsigned int height);

  ~Framework();

  void render();

 protected:
  // command buffers
  void initPoolCommandBuffer();
  void initCommandBuffersClearScreen();
  void initCommandBuffersScene();

  void initSemaphoreImageAcquired();
  void initFenceDraw();

  void queueCommandDrawScene(unsigned int width, unsigned int height);
  void queueCommandBuffersClearScreen();

 protected:
  static constexpr unsigned int IMAGES_SWAPCHAIN = 2;

  /* Number of samples needs to be the same at image creation,      */
  /* renderpass creation and pipeline creation.                     */
  static constexpr VkSampleCountFlagBits SAMPLES_COUNT = VK_SAMPLE_COUNT_1_BIT;

  /* Number of viewports and number of scissors have to be the same */
  /* at pipeline creation and in any call to set them dynamically   */
  /* They also have to be the same as each other                    */
  static constexpr unsigned int VIEWPORT_COUNT = 1;

  /* Amount of time, in nanoseconds, to wait for a command buffer to complete */
  static constexpr unsigned int FENCE_TIMEOUT_NS = 100000000;

  std::string mAppName;

  //Window mWindow; todocontext instead
  Platform mPlatform;

  std::array<VkImage, IMAGES_SWAPCHAIN> mImages;
  std::array<VkImageView, IMAGES_SWAPCHAIN> mImageViews;
  std::array<VkFramebuffer, IMAGES_SWAPCHAIN> mFramebuffers;
  VkSwapchainKHR mSwapChain;

  // Per thread
  VkQueue mQueue;
  VkCommandPool mPoolCommand;
  std::vector<VkCommandBuffer> mCommandBuffers;

  // One command buffer each presentation image
  std::array<VkCommandBuffer, IMAGES_SWAPCHAIN> mClearScreenCommandBuffers;
  VkCommandBuffer mDrawCommandBuffer;

 private:
  void initSwapChain();

 protected:
  void initDepthBuffer(unsigned int width, unsigned int height);
  VkFormat mColorFormat;
  VkFormat mDepthFormat;
  VkImage mDepthImage;
  VkDeviceMemory mDepthMemory;
  VkImageView mDepthView;

  VkClearValue mClearColor;
  VkClearValue mClearDepthStencil;

  void initFramebuffers(unsigned int width, unsigned int height, bool includeDepth = true);

  void initRenderpass(bool includeDepth, bool clear, VkImageLayout finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
  VkRenderPass mRenderPass;

  void initStagingBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
  StagingBuffer mStagingBuffer;

  void initBufferVertex(VertexBuffer& vertexBuffer);
  VertexBuffer mVertexBuffer;

  void initBufferUniform(unsigned int width, unsigned int height);
  UniformBuffer mUniformBuffer;

  void initTexture(const char* texturePath);
  Texture mTexture;

  static constexpr unsigned int SHADER_STAGE_ID_VERTEX = 0;
  static constexpr unsigned int SHADER_STAGE_ID_FRAGMENT = 1;

  VkShaderModule initShaderModule(const char* vertexBufferPath);
  void initPipeline(unsigned int width, unsigned int height, const char* vertShaderPath, const char* fragShaderPath);
  VkPipeline mPipeline;
  VkPipelineLayout mPipelineLayout;
  VkShaderModule mFragmentShader;
  VkShaderModule mVertexShader;


  std::vector<Texture> mTextures;

  VkSemaphore mSemaphoreImageAquired;
  VkFence mFenceDraw;

  /* Number of descriptor sets needs to be the same at alloc,       */
  /* pipeline layout creation, and descriptor set layout creation   */
  static constexpr unsigned int DESCRIPTOR_SETS_COUNT = 1;
  static constexpr unsigned int DESCRIPTOR_SET_ID_UBO = 0;

  static constexpr unsigned int DESCRIPTOR_SET_BINDING_UBO = 0;
  static constexpr unsigned int DESCRIPTOR_SET_BINDING_TEXTURE = 1;
  static constexpr unsigned int DESCRIPTOR_SET_BINDING_COUNT = 2;

  void initPoolDescriptor(); // per thread
  void initDescriptorSets();
  void initDescriptorSetLayouts();
  std::vector<VkDescriptorSet> mDestriptorSets;
  std::vector<VkDescriptorSetLayout> mDestriptorSetLayouts;
  VkDescriptorPool mPoolDescriptor;
};

} // namespace rwc
