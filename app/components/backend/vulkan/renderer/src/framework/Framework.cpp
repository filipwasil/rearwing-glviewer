
#include <framework/Framework.hpp>
#include <Log.hpp>
#include <cstring>
#include <tuple>
#include <vk_mem_alloc.h>
#include <File.hpp>
#include <Math.hpp>

#include "cube_textured.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace rwc {

Framework::Framework(const char* appName, unsigned int width, unsigned int height)
  : mWindow{appName, width, height}
  , mPlatform{appName, mWindow}
  , mColorFormat{VK_FORMAT_B8G8R8A8_UNORM}
  , mDepthFormat{VK_FORMAT_D16_UNORM}
  , mClearColor{VkClearColorValue{0.0,0.5,0.0,1.0}}
  , mClearDepthStencil{1.0, 1.0}
  , mRenderPass{}
  , mVertexBuffer{textured_cube_buffer}
  , mUniformBuffer{}
  , mTexture{}
  , mSemaphoreImageAquired{}
  , mFenceDraw{} {

  vkGetDeviceQueue(mPlatform.getDevice(), mPlatform.getQueueFamily(), 0, &mQueue);

  initSwapChain();
  initPoolCommandBuffer();
  initPoolDescriptor();
  initSemaphoreImageAcquired();
  initFenceDraw();

  initDepthBuffer(width, height);
  initBufferVertex(mVertexBuffer);
  initBufferUniform(width, height);
  initTexture("");

  initRenderpass(true, true);
  initFramebuffers(width, height, true);

  initDescriptorSetLayouts();
  initDescriptorSets();

  initPipeline(width, height, "generated/shaders/test1/vs.spv", "generated/shaders/test1/fs.spv");

  initCommandBuffersClearScreen();
  initCommandBuffersScene();

  queueCommandDrawScene(width, height);
}

Framework::~Framework() {
  vkDestroySemaphore(mPlatform.getDevice(), mSemaphoreImageAquired, nullptr);
  vkDestroyBuffer(mPlatform.getDevice(), mVertexBuffer.mBufferData.mBuffer, nullptr);
  vkFreeMemory(mPlatform.getDevice(), mVertexBuffer.mBufferData.mMemory, nullptr);
  //need to call for texture
  //stbi_image_free(pixels);
  vkDestroyDescriptorPool(mPlatform.getDevice(), mPoolDescriptor, nullptr);
}

void Framework::initSwapChain() {
  const VkSurfaceCapabilitiesKHR& surfaceCapabilities = mPlatform.getSurfaceCapabilities();

  VkSwapchainCreateInfoKHR SwapChainCreateInfo = {};

  SwapChainCreateInfo.sType            = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  SwapChainCreateInfo.surface          = mPlatform.getSurface();
  SwapChainCreateInfo.minImageCount    = IMAGES_SWAPCHAIN;
  SwapChainCreateInfo.imageFormat      = mPlatform.getSurfaceFormat().format;
  SwapChainCreateInfo.imageColorSpace  = mPlatform.getSurfaceFormat().colorSpace;
  SwapChainCreateInfo.imageExtent      = surfaceCapabilities.currentExtent;
  SwapChainCreateInfo.imageUsage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  SwapChainCreateInfo.preTransform     = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
  SwapChainCreateInfo.imageArrayLayers = 1;
  SwapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
  SwapChainCreateInfo.presentMode      = VK_PRESENT_MODE_FIFO_KHR;
  SwapChainCreateInfo.clipped          = true;
  SwapChainCreateInfo.compositeAlpha   = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

  VkResult res = vkCreateSwapchainKHR(mPlatform.getDevice(), &SwapChainCreateInfo, nullptr, &mSwapChain);
  logC("vkCreateSwapchainKHR error", res);

  printf("Swap chain created\n");

  uint NumSwapChainImages = 0;
  res = vkGetSwapchainImagesKHR(mPlatform.getDevice(), mSwapChain, &NumSwapChainImages, nullptr);
  logC("vkGetSwapchainImagesKHR error ", res);

  if(IMAGES_SWAPCHAIN != NumSwapChainImages
     || IMAGES_SWAPCHAIN < surfaceCapabilities.minImageCount
     || IMAGES_SWAPCHAIN > surfaceCapabilities.maxImageCount) {
    logF("Swap images count wrong");
  }

  printf("Number of images %d\n", NumSwapChainImages);

  res = vkGetSwapchainImagesKHR(mPlatform.getDevice(), mSwapChain, &NumSwapChainImages, &(mImages[0]));
  logC("vkGetSwapchainImagesKHR error ", res);

  for (uint32_t i = 0; i < NumSwapChainImages; i++) {
    VkImageViewCreateInfo colorImageView = {};
    colorImageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    colorImageView.pNext = nullptr;
    colorImageView.format = mColorFormat;
    colorImageView.components.r = VK_COMPONENT_SWIZZLE_R;
    colorImageView.components.g = VK_COMPONENT_SWIZZLE_G;
    colorImageView.components.b = VK_COMPONENT_SWIZZLE_B;
    colorImageView.components.a = VK_COMPONENT_SWIZZLE_A;
    colorImageView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    colorImageView.subresourceRange.baseMipLevel = 0;
    colorImageView.subresourceRange.levelCount = 1;
    colorImageView.subresourceRange.baseArrayLayer = 0;
    colorImageView.subresourceRange.layerCount = 1;
    colorImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
    colorImageView.flags = 0;

    colorImageView.image = mImages[i];

    res = vkCreateImageView(mPlatform.getDevice(), &colorImageView, nullptr, &mImageViews[i]);
  }
}

void Framework::initPoolCommandBuffer() {
  VkCommandPoolCreateInfo cmdPoolCreateInfo = {};
  cmdPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  cmdPoolCreateInfo.queueFamilyIndex = mPlatform.getQueueFamily();

  VkResult res = vkCreateCommandPool(mPlatform.getDevice(), &cmdPoolCreateInfo, nullptr, &mPoolCommand);
  logC("vkCreateCommandPool error ", res);

  logD("Command buffer pool created");
}

void Framework::initPoolDescriptor() {
  VkDescriptorPoolSize type_count[2];
  type_count[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  type_count[0].descriptorCount = 1;
  type_count[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  type_count[1].descriptorCount = 1;

  VkDescriptorPoolCreateInfo descriptor_pool = {};
  descriptor_pool.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  descriptor_pool.pNext = nullptr;
  descriptor_pool.maxSets = 1;
  descriptor_pool.poolSizeCount = 2;
  descriptor_pool.pPoolSizes = type_count;

  logC("vkCreateDescriptorPool"
       , vkCreateDescriptorPool(mPlatform.getDevice(), &descriptor_pool, nullptr, &mPoolDescriptor));
}

void Framework::initDescriptorSetLayouts() {
  VkDescriptorSetLayoutBinding layout_bindings[DESCRIPTOR_SET_BINDING_COUNT];
  layout_bindings[DESCRIPTOR_SET_BINDING_UBO].binding = DESCRIPTOR_SET_BINDING_UBO;
  layout_bindings[DESCRIPTOR_SET_BINDING_UBO].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  layout_bindings[DESCRIPTOR_SET_BINDING_UBO].descriptorCount = 1;
  layout_bindings[DESCRIPTOR_SET_BINDING_UBO].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
  layout_bindings[DESCRIPTOR_SET_BINDING_UBO].pImmutableSamplers = nullptr;

  layout_bindings[DESCRIPTOR_SET_BINDING_TEXTURE].binding = DESCRIPTOR_SET_BINDING_TEXTURE;
  layout_bindings[DESCRIPTOR_SET_BINDING_TEXTURE].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  layout_bindings[DESCRIPTOR_SET_BINDING_TEXTURE].descriptorCount = 1;
  layout_bindings[DESCRIPTOR_SET_BINDING_TEXTURE].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
  layout_bindings[DESCRIPTOR_SET_BINDING_TEXTURE].pImmutableSamplers = nullptr;

  /* Next take layout bindings and use them to create a descriptor set layout
   */
  VkDescriptorSetLayoutCreateInfo descriptor_layout = {};
  descriptor_layout.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  descriptor_layout.pNext = nullptr;
  descriptor_layout.flags = 0;
  descriptor_layout.bindingCount = DESCRIPTOR_SET_BINDING_COUNT;
  descriptor_layout.pBindings = layout_bindings;

  mDestriptorSetLayouts.resize(DESCRIPTOR_SETS_COUNT);
  logC("vkCreateDescriptorSetLayout"
       , vkCreateDescriptorSetLayout(mPlatform.getDevice(), &descriptor_layout, nullptr, mDestriptorSetLayouts.data()));
}

void Framework::initDescriptorSets() {
  mDestriptorSets.resize(DESCRIPTOR_SETS_COUNT);

  VkDescriptorSetAllocateInfo alloc_info[DESCRIPTOR_SETS_COUNT];
  alloc_info[0].sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  alloc_info[0].pNext = nullptr;
  alloc_info[0].descriptorPool = mPoolDescriptor;
  alloc_info[0].descriptorSetCount = DESCRIPTOR_SETS_COUNT;
  alloc_info[0].pSetLayouts = mDestriptorSetLayouts.data();

  logC("vkAllocateDescriptorSets error"
       , vkAllocateDescriptorSets(mPlatform.getDevice(), alloc_info, mDestriptorSets.data()));

  VkWriteDescriptorSet writes[DESCRIPTOR_SETS_COUNT];
  writes[DESCRIPTOR_SET_ID_UBO] = {};
  writes[DESCRIPTOR_SET_ID_UBO].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  writes[DESCRIPTOR_SET_ID_UBO].pNext = nullptr;
  writes[DESCRIPTOR_SET_ID_UBO].dstSet = mDestriptorSets[DESCRIPTOR_SET_ID_UBO];
  writes[DESCRIPTOR_SET_ID_UBO].descriptorCount = DESCRIPTOR_SETS_COUNT;
  writes[DESCRIPTOR_SET_ID_UBO].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  writes[DESCRIPTOR_SET_ID_UBO].pBufferInfo = &mUniformBuffer.mBufferData.mDescriptorInfo;
  writes[DESCRIPTOR_SET_ID_UBO].dstArrayElement = 0;
  writes[DESCRIPTOR_SET_ID_UBO].dstBinding = DESCRIPTOR_SET_BINDING_UBO;

  vkUpdateDescriptorSets(mPlatform.getDevice(), DESCRIPTOR_SETS_COUNT, writes, 0, nullptr);
}

void Framework::initCommandBuffersClearScreen() {
  VkCommandBufferAllocateInfo cmdBufAllocInfo = {};
  cmdBufAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  cmdBufAllocInfo.commandPool = mPoolCommand;
  cmdBufAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  cmdBufAllocInfo.commandBufferCount = mImages.size();

  logC("vkAllocateCommandBuffers error "
       , vkAllocateCommandBuffers(mPlatform.getDevice(), &cmdBufAllocInfo, &mClearScreenCommandBuffers[0]));

  logD("Created command buffers");
}

void Framework::initCommandBuffersScene() {
  VkCommandBufferAllocateInfo cmdBufAllocInfo = {};
  cmdBufAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  cmdBufAllocInfo.commandPool = mPoolCommand;
  cmdBufAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  cmdBufAllocInfo.commandBufferCount = 1;

  logC("vkAllocateCommandBuffers error "
    , vkAllocateCommandBuffers(mPlatform.getDevice(), &cmdBufAllocInfo, &mDrawCommandBuffer));

  logD("Created command buffers");
}

void Framework::initDepthBuffer(unsigned int width, unsigned int height) {
  VkImageCreateInfo image_info = {};

  VkFormatProperties props;
  vkGetPhysicalDeviceFormatProperties(mPlatform.getPhysicalDevice(), mDepthFormat, &props);
  if (props.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
    image_info.tiling = VK_IMAGE_TILING_LINEAR;
  } else if (props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
    image_info.tiling = VK_IMAGE_TILING_OPTIMAL;
  } else {
    logF("depth_format unsupported");
  }

  image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  image_info.pNext = nullptr;
  image_info.imageType = VK_IMAGE_TYPE_2D;
  image_info.format = mDepthFormat;
  image_info.extent.width = width;
  image_info.extent.height = height;
  image_info.extent.depth = 1;
  image_info.mipLevels = 1;
  image_info.arrayLayers = 1;
  image_info.samples = SAMPLES_COUNT;
  image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  image_info.queueFamilyIndexCount = 0;
  image_info.pQueueFamilyIndices = nullptr;
  image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  image_info.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
  image_info.flags = 0;

  VkMemoryAllocateInfo mem_alloc = {};
  mem_alloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  mem_alloc.pNext = nullptr;
  mem_alloc.allocationSize = 0;
  mem_alloc.memoryTypeIndex = 0;

  VkImageViewCreateInfo view_info = {};
  view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  view_info.pNext = nullptr;
  view_info.image = nullptr;
  view_info.format = mDepthFormat;
  view_info.components.r = VK_COMPONENT_SWIZZLE_R;
  view_info.components.g = VK_COMPONENT_SWIZZLE_G;
  view_info.components.b = VK_COMPONENT_SWIZZLE_B;
  view_info.components.a = VK_COMPONENT_SWIZZLE_A;
  view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
  view_info.subresourceRange.baseMipLevel = 0;
  view_info.subresourceRange.levelCount = 1;
  view_info.subresourceRange.baseArrayLayer = 0;
  view_info.subresourceRange.layerCount = 1;
  view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
  view_info.flags = 0;

  if (mDepthFormat == VK_FORMAT_D16_UNORM_S8_UINT
      || mDepthFormat == VK_FORMAT_D24_UNORM_S8_UINT
      || mDepthFormat == VK_FORMAT_D32_SFLOAT_S8_UINT) {
    view_info.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
  }

  VkMemoryRequirements mem_reqs;

  /* Create image */
  logC("vkCreateImage", vkCreateImage(mPlatform.getDevice(), &image_info, nullptr, &mDepthImage));
  vkGetImageMemoryRequirements(mPlatform.getDevice(), mDepthImage, &mem_reqs);

  mem_alloc.allocationSize = mem_reqs.size;
  /* Use the memory properties to determine the type of memory required */
  mem_alloc.memoryTypeIndex =
    mPlatform.getFirstValidMemoryTypeIdx(mem_reqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

  /* Allocate memory */
  logC("vkAllocateMemory ", vkAllocateMemory(mPlatform.getDevice(), &mem_alloc, nullptr, &mDepthMemory));

  /* Bind memory */
  logC("vkBindImageMemory ", vkBindImageMemory(mPlatform.getDevice(), mDepthImage, mDepthMemory, 0));

  /* Create image view */
  view_info.image = mDepthImage;
  logC("vkCreateImageView ", vkCreateImageView(mPlatform.getDevice(), &view_info, nullptr, &mDepthView));
}

void Framework::initRenderpass(bool includeDepth, bool clear, VkImageLayout finalLayout) {
  /* DEPENDS on init_swap_chain() and init_depth_buffer() */

  /* Need attachments for render target and depth buffer */
  VkAttachmentDescription attachments[2];
  attachments[0].format = mColorFormat;
  attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
  attachments[0].loadOp = clear ? VK_ATTACHMENT_LOAD_OP_CLEAR : VK_ATTACHMENT_LOAD_OP_LOAD;
  attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  attachments[0].finalLayout = finalLayout;
  attachments[0].flags = 0;

  if (includeDepth) {
    attachments[1].format = mDepthFormat;
    attachments[1].samples = VK_SAMPLE_COUNT_1_BIT;
    attachments[1].loadOp = clear ? VK_ATTACHMENT_LOAD_OP_CLEAR : VK_ATTACHMENT_LOAD_OP_LOAD;
    attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
    attachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachments[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    attachments[1].flags = 0;
  }

  VkAttachmentReference color_reference = {};
  color_reference.attachment = 0;
  color_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  VkAttachmentReference depth_reference = {};
  depth_reference.attachment = 1;
  depth_reference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  VkSubpassDescription subpass = {};
  subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass.flags = 0;
  subpass.inputAttachmentCount = 0;
  subpass.pInputAttachments = nullptr;
  subpass.colorAttachmentCount = 1;
  subpass.pColorAttachments = &color_reference;
  subpass.pResolveAttachments = nullptr;
  subpass.pDepthStencilAttachment = includeDepth ? &depth_reference : nullptr;
  subpass.preserveAttachmentCount = 0;
  subpass.pPreserveAttachments = nullptr;

  VkRenderPassCreateInfo rp_info = {};
  rp_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  rp_info.pNext = nullptr;
  rp_info.attachmentCount = includeDepth ? 2 : 1;
  rp_info.pAttachments = attachments;
  rp_info.subpassCount = 1;
  rp_info.pSubpasses = &subpass;
  rp_info.dependencyCount = 0;
  rp_info.pDependencies = nullptr;

  logC("vkCreateRenderPass", vkCreateRenderPass(mPlatform.getDevice(), &rp_info, nullptr, &mRenderPass));
}

void Framework::initFramebuffers(unsigned int width, unsigned int height, bool include_depth) {
  /* DEPENDS on init_depth_buffer(), init_renderpass() and
   * init_swapchain_extension() */

  VkImageView attachments[2];
  attachments[1] = mDepthView;

  VkFramebufferCreateInfo fb_info = {};
  fb_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
  fb_info.pNext = nullptr;
  fb_info.renderPass = mRenderPass;
  fb_info.attachmentCount = include_depth ? 2 : 1;
  fb_info.pAttachments = attachments;
  fb_info.width = width;
  fb_info.height = height;
  fb_info.layers = 1;

  uint32_t i;

  for (i = 0; i < IMAGES_SWAPCHAIN; ++i) {
    attachments[0] = mImageViews[i];
    logC("vkCreateFramebuffer ", vkCreateFramebuffer(mPlatform.getDevice(), &fb_info, nullptr, &mFramebuffers[i]));
  }
}

VkShaderModule Framework::initShaderModule(const char* shaderPath) {

  const std::vector<char> shaderModuleData = readBinary(shaderPath);
  VkShaderModuleCreateInfo shaderCreateInfo = {};
  shaderCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  shaderCreateInfo.codeSize = shaderModuleData.size();
  shaderCreateInfo.pCode = reinterpret_cast<const uint32_t*>(shaderModuleData.data());

  VkShaderModule shaderModule;
  VkResult res = vkCreateShaderModule(mPlatform.getDevice(), &shaderCreateInfo, nullptr, &shaderModule);
  logC("vkCreateShaderModule error ", res);
  logD("Created shader " + std::string(shaderPath));
  return shaderModule;
}

void Framework::initPipeline(
  unsigned int width
  , unsigned int height
  , const char* vertShaderPath
  , const char* fragShaderPath) {
  std::array<VkPipelineShaderStageCreateInfo, 2> shaderStageCreateInfo = { { } };

  shaderStageCreateInfo[SHADER_STAGE_ID_VERTEX].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  shaderStageCreateInfo[SHADER_STAGE_ID_VERTEX].stage = VK_SHADER_STAGE_VERTEX_BIT;
  shaderStageCreateInfo[SHADER_STAGE_ID_VERTEX].module = initShaderModule(vertShaderPath);
  shaderStageCreateInfo[SHADER_STAGE_ID_VERTEX].pName = "main";
  shaderStageCreateInfo[SHADER_STAGE_ID_FRAGMENT].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  shaderStageCreateInfo[SHADER_STAGE_ID_FRAGMENT].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  shaderStageCreateInfo[SHADER_STAGE_ID_FRAGMENT].module = initShaderModule(fragShaderPath);;
  shaderStageCreateInfo[SHADER_STAGE_ID_FRAGMENT].pName = "main";

  VkPipelineVertexInputStateCreateInfo vi = {};
  VkPipelineInputAssemblyStateCreateInfo ia = {};

  // VBO
  vi.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  vi.pNext = nullptr;
  vi.flags = 0;
  vi.vertexBindingDescriptionCount = 1;
  vi.pVertexBindingDescriptions = &mVertexBuffer.mVertexInputBinding;
  vi.vertexAttributeDescriptionCount = mVertexBuffer.mTupleSize;
  vi.pVertexAttributeDescriptions = mVertexBuffer.mVertexInputAttributeDescription.data();

  ia.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  ia.pNext = nullptr;
  ia.flags = 0;
  ia.primitiveRestartEnable = VK_FALSE;
  ia.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

//  No VBO
//  vi.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
//  vi.vertexBindingDescriptionCount = 0;
//  vi.pVertexBindingDescriptions = nullptr; // Optional
//  vi.vertexAttributeDescriptionCount = 0;
//  vi.pVertexAttributeDescriptions = nullptr; // Optional

//  ia.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
//  ia.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
//  ia.primitiveRestartEnable = VK_FALSE;

  VkViewport vp = {};
  vp.x = 0.0f;
  vp.y = 0.0f;
  vp.width  = static_cast<float>(width);
  vp.height = static_cast<float>(height);
  vp.minDepth = 0.0f;
  vp.maxDepth = 1.0f;

  VkRect2D scissor = {};
  scissor.offset = {0, 0};
  scissor.extent = {};

  VkPipelineViewportStateCreateInfo vpCreateInfo = {};
  vpCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  vpCreateInfo.viewportCount = 1;
  vpCreateInfo.pViewports = &vp;
  vpCreateInfo.scissorCount = 1;
  vpCreateInfo.pScissors = &scissor;

  VkPipelineRasterizationStateCreateInfo rastCreateInfo = {};
  rastCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rastCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
  rastCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
  rastCreateInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
  rastCreateInfo.lineWidth = 1.0f;

  VkPipelineMultisampleStateCreateInfo pipelineMSCreateInfo = {};
  pipelineMSCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;

  VkPipelineColorBlendAttachmentState blendAttachState = {};
  blendAttachState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

  // Blending
  blendAttachState.blendEnable = VK_TRUE;
  blendAttachState.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
  blendAttachState.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
  blendAttachState.colorBlendOp = VK_BLEND_OP_ADD;
  blendAttachState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
  blendAttachState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
  blendAttachState.alphaBlendOp = VK_BLEND_OP_ADD;
  // No blending
//  blendAttachState.blendEnable = VK_FALSE;
//  blendAttachState.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
//  blendAttachState.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
//  blendAttachState.colorBlendOp = VK_BLEND_OP_ADD; // Optional
//  blendAttachState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
//  blendAttachState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
//  blendAttachState.alphaBlendOp = VK_BLEND_OP_ADD; // Optional


  VkPipelineColorBlendStateCreateInfo blendCreateInfo = {};
  blendCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  blendCreateInfo.logicOp = VK_LOGIC_OP_COPY;
  blendCreateInfo.attachmentCount = 1;
  blendCreateInfo.pAttachments = &blendAttachState;

  VkPipelineDepthStencilStateCreateInfo ds;
  ds.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
  ds.pNext = nullptr;
  ds.flags = 0;
  ds.depthTestEnable = 0;
  ds.depthWriteEnable = 0;
  ds.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
  ds.depthBoundsTestEnable = VK_FALSE;
  ds.stencilTestEnable = VK_FALSE;
  ds.back.failOp = VK_STENCIL_OP_KEEP;
  ds.back.passOp = VK_STENCIL_OP_KEEP;
  ds.back.compareOp = VK_COMPARE_OP_ALWAYS;
  ds.back.compareMask = 0;
  ds.back.reference = 0;
  ds.back.depthFailOp = VK_STENCIL_OP_KEEP;
  ds.back.writeMask = 0;
  ds.minDepthBounds = 0;
  ds.maxDepthBounds = 0;
  ds.stencilTestEnable = VK_FALSE;
  ds.front = ds.back;

  VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
  pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipelineLayoutInfo.setLayoutCount = 0; // Optional
  pipelineLayoutInfo.pSetLayouts = mDestriptorSetLayouts.data(); // Optional
  pipelineLayoutInfo.setLayoutCount = DESCRIPTOR_SETS_COUNT; // Optional
  pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
  pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

  if (vkCreatePipelineLayout(mPlatform.getDevice(), &pipelineLayoutInfo, nullptr, &mPipelineLayout) != VK_SUCCESS) {
    throw std::runtime_error("failed to create pipeline layout!");
  }

  VkGraphicsPipelineCreateInfo pipelineInfo = {};
  pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pipelineInfo.stageCount = shaderStageCreateInfo.size();
  pipelineInfo.pStages = &shaderStageCreateInfo[0];
  pipelineInfo.pVertexInputState = &vi;
  pipelineInfo.pInputAssemblyState = &ia;
  pipelineInfo.pViewportState = &vpCreateInfo;
  pipelineInfo.pRasterizationState = &rastCreateInfo;
  pipelineInfo.pMultisampleState = &pipelineMSCreateInfo;
  pipelineInfo.pColorBlendState = &blendCreateInfo;
  pipelineInfo.renderPass = mRenderPass;
  pipelineInfo.basePipelineIndex = 0;
  pipelineInfo.layout = mPipelineLayout;
  pipelineInfo.pDepthStencilState = &ds;

  logC("vkCreateGraphicsPipelines error "
       , vkCreateGraphicsPipelines(mPlatform.getDevice(), nullptr, 1, &pipelineInfo, nullptr, &mPipeline));

  printf("Graphics pipeline created\n");
}

void Framework::initBufferVertex(VertexBuffer& vertexBuffer) {
/*
 * Set up a vertex buffer:
 * - Create a buffer
 * - Map it and write the vertex data into it
 * - Bind it using vkCmdBindVertexBuffers
 * - Later, at pipeline creation,
 * -      fill in vertex input part of the pipeline with relevent data
 */

  logC("Can not create Vertex Buffer with empty data buffer", vertexBuffer.mData.empty());
  VkBufferCreateInfo buf_info = {};
  buf_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  buf_info.pNext = nullptr;
  buf_info.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
  buf_info.size = vertexBuffer.mData.size();
  buf_info.queueFamilyIndexCount = 0;
  buf_info.pQueueFamilyIndices = nullptr;
  buf_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  buf_info.flags = 0;
  logC("vkCreateBuffer ", vkCreateBuffer(mPlatform.getDevice(), &buf_info, nullptr, &vertexBuffer.mBufferData.mBuffer));

  VkMemoryRequirements mem_reqs;
  vkGetBufferMemoryRequirements(mPlatform.getDevice(), vertexBuffer.mBufferData.mBuffer, &mem_reqs);

  VkMemoryAllocateInfo alloc_info = {};
  alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  alloc_info.pNext = nullptr;
  alloc_info.memoryTypeIndex = 0;

  alloc_info.allocationSize = mem_reqs.size;
  alloc_info.memoryTypeIndex = mPlatform.getFirstValidMemoryTypeIdx(
    mem_reqs.memoryTypeBits
    , VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

  logC("vkAllocateMemory "
    , vkAllocateMemory(mPlatform.getDevice(), &alloc_info, nullptr, &(vertexBuffer.mBufferData.mMemory)));

  uint8_t* pData;
  logC("vkMapMemory ",
       vkMapMemory(
         mPlatform.getDevice(), vertexBuffer.mBufferData.mMemory, 0, mem_reqs.size, 0, reinterpret_cast<void **>(&pData)));

  memcpy(pData, vertexBuffer.mData.data(), vertexBuffer.mData.size());

  vkUnmapMemory(mPlatform.getDevice(),vertexBuffer.mBufferData.mMemory);

  logC("vkBindBufferMemory"
    , vkBindBufferMemory(mPlatform.getDevice()
      , vertexBuffer.mBufferData.mBuffer
      , vertexBuffer.mBufferData.mMemory
      , 0));

  /* We won't use these here, but we will need this info when creating the
   * pipeline */
  vertexBuffer.mVertexInputBinding.binding = 0;
  vertexBuffer.mVertexInputBinding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
  vertexBuffer.mVertexInputBinding.stride = vertexBuffer.mStride;
}

void Framework::initBufferUniform(unsigned int width, unsigned int height) {
  VkResult res = VK_SUCCESS;
  bool pass = true;

  auto mvp = getMVP(width, height);
  const auto mvpSize = sizeof(mvp);

  /* VULKAN_KEY_START */
  VkBufferCreateInfo buf_info = {};
  buf_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  buf_info.pNext = nullptr;
  buf_info.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
  buf_info.size = mvpSize;
  buf_info.queueFamilyIndexCount = 0;
  buf_info.pQueueFamilyIndices = nullptr;
  buf_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  buf_info.flags = 0;
  res = vkCreateBuffer(mPlatform.getDevice(), &buf_info, nullptr, &mUniformBuffer.mBufferData.mBuffer);
  assert(res == VK_SUCCESS);

  VkMemoryRequirements mem_reqs;
  vkGetBufferMemoryRequirements(mPlatform.getDevice(), mUniformBuffer.mBufferData.mBuffer, &mem_reqs);

  VkMemoryAllocateInfo alloc_info = {};
  alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  alloc_info.pNext = nullptr;
  alloc_info.memoryTypeIndex = 0;

  alloc_info.allocationSize = mem_reqs.size;

  alloc_info.memoryTypeIndex =
    mPlatform.getFirstValidMemoryTypeIdx(mem_reqs.memoryTypeBits
    , VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

  assert(pass && "No mappable, coherent memory");

  logC("vkAllocateMemory error "
    , vkAllocateMemory(mPlatform.getDevice(), &alloc_info, nullptr, &(mUniformBuffer.mBufferData.mMemory)));

  uint8_t* data;
  logC("vkMapMemory error "
    , vkMapMemory(
      mPlatform.getDevice(), mUniformBuffer.mBufferData.mMemory, 0, mem_reqs.size, 0, reinterpret_cast<void **>(&data)));

  memcpy(data, &mvp, mvpSize);

  vkUnmapMemory(mPlatform.getDevice(), mUniformBuffer.mBufferData.mMemory);

  logC("vkBindBufferMemory error "
       , vkBindBufferMemory(mPlatform.getDevice()
         , mUniformBuffer.mBufferData.mBuffer
         , mUniformBuffer.mBufferData.mMemory, 0));

  mUniformBuffer.mBufferData.mDescriptorInfo.buffer = mUniformBuffer.mBufferData.mBuffer;
  mUniformBuffer.mBufferData.mDescriptorInfo.offset = 0;
  mUniformBuffer.mBufferData.mDescriptorInfo.range = mvpSize;
}

void Framework::initTexture(const char* texturePath) {
  int texChannels= 0;

  stbi_uc* pixels = stbi_load(texturePath, &mTexture.mWidth, &mTexture.mHeight, &texChannels, STBI_rgb_alpha);
  if (!pixels || mTexture.mWidth <= 0 || mTexture.mHeight <= 0) {
    throw std::runtime_error("failed to load texture image!");
  }

  const unsigned int RGBACount = 4;
  VkDeviceSize imageSize =
    static_cast<unsigned int>(mTexture.mWidth) * static_cast<unsigned int>(mTexture.mHeight) * RGBACount;

  initStagingBuffer(imageSize, 0,0);
//  createBuffer(
//    imageSize
//    , VK_BUFFER_USAGE_TRANSFER_SRC_BIT
//    , VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
//    , stagingBuffer
//    , stagingBufferMemory);
//
//  void* data;
//  vkMapMemory(mPlatform.getDevice()
//    , stagingBufferMemory
//    , 0
//    , imageSize
//    , 0, &data);
//
//  memcpy(data, pixels, static_cast<size_t>(imageSize));
//  vkUnmapMemory(mPlatform.getDevice(), stagingBufferMemory);
}

void Framework::initStagingBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags /*properties*/) {
  VkBufferCreateInfo bufferInfo = {};
  bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  bufferInfo.size = size;
  bufferInfo.usage = usage;
  bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  if (vkCreateBuffer(mPlatform.getDevice(), &bufferInfo, nullptr, &mStagingBuffer.mBufferData.mBuffer) != VK_SUCCESS) {
    throw std::runtime_error("failed to create buffer!");
  }

  VkMemoryRequirements memRequirements;
  vkGetBufferMemoryRequirements(mPlatform.getDevice(), mStagingBuffer.mBufferData.mBuffer, &memRequirements);

  VkMemoryAllocateInfo allocInfo = {};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;

  allocInfo.memoryTypeIndex =
    mPlatform.getFirstValidMemoryTypeIdx(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

  if (vkAllocateMemory(mPlatform.getDevice(), &allocInfo, nullptr, &mStagingBuffer.mBufferData.mMemory) != VK_SUCCESS) {
    throw std::runtime_error("failed to allocate buffer memory!");
  }

  vkBindBufferMemory(mPlatform.getDevice(), mStagingBuffer.mBufferData.mBuffer, mStagingBuffer.mBufferData.mMemory, 0);
}

void Framework::queueCommandBuffersClearScreen() {
  VkCommandBufferBeginInfo beginInfo = {};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

  VkImageSubresourceRange imageRange = {};
  imageRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  imageRange.levelCount = 1;
  imageRange.layerCount = 1;

  for (uint idx = 0 ; idx < mClearScreenCommandBuffers.size() ; ++idx) {
    logC("vkBeginCommandBuffer error "
         , vkBeginCommandBuffer(mClearScreenCommandBuffers[idx], &beginInfo));

    vkCmdClearColorImage(
      mClearScreenCommandBuffers[idx]
      , mImages[idx]
      , VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
      , &mClearColor.color
      , 1
      , &imageRange);

    logC("vkEndCommandBuffer error ", vkEndCommandBuffer(mClearScreenCommandBuffers[idx]));
  }

  logD("Command buffers recorded");
}

void Framework::queueCommandDrawScene(unsigned int width, unsigned int height) {
  unsigned int imageIdx = 0;

  VkCommandBufferBeginInfo beginInfo = {};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
  logC("vkBeginCommandBuffer error", vkBeginCommandBuffer(mDrawCommandBuffer, &beginInfo));

  VkRenderPassBeginInfo renderPassBegininfo;
  VkClearValue clearValues[2] { mClearColor, mClearDepthStencil };
  renderPassBegininfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderPassBegininfo.pNext = nullptr;
  renderPassBegininfo.renderPass = mRenderPass;
  renderPassBegininfo.framebuffer = mFramebuffers[imageIdx];
  renderPassBegininfo.renderArea.offset.x = 0;
  renderPassBegininfo.renderArea.offset.y = 0;
  renderPassBegininfo.renderArea.extent.width = width;
  renderPassBegininfo.renderArea.extent.height = height;
  renderPassBegininfo.clearValueCount = 2;
  renderPassBegininfo.pClearValues = clearValues;
  vkCmdBeginRenderPass(mDrawCommandBuffer, &renderPassBegininfo, VK_SUBPASS_CONTENTS_INLINE);

  // tmp

  vkCmdBindPipeline(mDrawCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, mPipeline);
  vkCmdBindDescriptorSets(
    mDrawCommandBuffer
    , VK_PIPELINE_BIND_POINT_GRAPHICS
    , mPipelineLayout
    , 0
    , DESCRIPTOR_SETS_COUNT
    , mDestriptorSets.data()
    , 0
    , nullptr);

  const VkDeviceSize offsets[1] = {0};
  vkCmdBindVertexBuffers(mDrawCommandBuffer, 0, 1, &mVertexBuffer.mBufferData.mBuffer, offsets);

//  init_viewports(info);
//  init_scissors(info);

  vkCmdDraw(mDrawCommandBuffer, 12 * 3, 1, 0, 0);
  vkCmdEndRenderPass(mDrawCommandBuffer);
  logC("vkEndCommandBuffer error", vkEndCommandBuffer(mDrawCommandBuffer));
}

void Framework::initSemaphoreImageAcquired() {
  VkSemaphoreCreateInfo imageAcquiredSemaphoreCreateInfo;
  imageAcquiredSemaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
  imageAcquiredSemaphoreCreateInfo.pNext = nullptr;
  imageAcquiredSemaphoreCreateInfo.flags = 0;

  logC("vkCreateSemaphore error"
       , vkCreateSemaphore(mPlatform.getDevice(), &imageAcquiredSemaphoreCreateInfo, nullptr, &mSemaphoreImageAquired));
}

void Framework::initFenceDraw() {
  VkFenceCreateInfo fenceInfo;
  fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fenceInfo.pNext = nullptr;
  fenceInfo.flags = 0;
  vkCreateFence(mPlatform.getDevice(), &fenceInfo, nullptr, &mFenceDraw);
}

void Framework::render() {
  unsigned int imageIdx = 0;

  logC("vkAcquireNextImageKHR error "
    ,vkAcquireNextImageKHR(mPlatform.getDevice(), mSwapChain, UINT64_MAX, mSemaphoreImageAquired, nullptr, &imageIdx));

  mCommandBuffers.insert(mCommandBuffers.end(), mClearScreenCommandBuffers.begin(), mClearScreenCommandBuffers.end());
  mCommandBuffers.push_back(mDrawCommandBuffer);

  VkSubmitInfo submitInfo = {};
  submitInfo.sType                = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submitInfo.commandBufferCount   = mCommandBuffers.size();
  submitInfo.pCommandBuffers      = mCommandBuffers.data();

  logC("vkQueueSubmit error ", vkQueueSubmit(mQueue, 1, &submitInfo, mFenceDraw));

  while (vkWaitForFences(mPlatform.getDevice(), 1, &mFenceDraw, VK_TRUE, FENCE_TIMEOUT_NS) == VK_TIMEOUT);

  VkPresentInfoKHR presentInfo = {};
  presentInfo.sType              = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  presentInfo.swapchainCount     = 1;
  presentInfo.pSwapchains        = &mSwapChain;
  presentInfo.pImageIndices      = &imageIdx;

  logC("vkQueuePresentKHR error " , vkQueuePresentKHR(mQueue, &presentInfo));
}

} // namespace rwc
