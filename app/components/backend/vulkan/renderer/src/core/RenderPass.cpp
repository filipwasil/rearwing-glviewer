/* Copyright (C) Filip Wasil, All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Filip Wasil <fillwave@gmail.com>
 */

#include <core/RenderPass.hpp>

namespace rwc {

RenderPass::RenderPass() {
//  // A semaphore (or fence) is required in order to acquire a
//  // swapchain image to prepare it for use in a render pass.
//  // The semaphore is normally used to hold back the rendering
//  // operation until the image is actually available.
//  // But since this sample does not render, the semaphore
//  // ends up being unused.
//  VkSemaphore imageAcquiredSemaphore;
//  VkSemaphoreCreateInfo imageAcquiredSemaphoreCreateInfo;
//  imageAcquiredSemaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
//  imageAcquiredSemaphoreCreateInfo.pNext = NULL;
//  imageAcquiredSemaphoreCreateInfo.flags = 0;
//
//  res = vkCreateSemaphore(info.device, &imageAcquiredSemaphoreCreateInfo, NULL, &imageAcquiredSemaphore);
//  assert(res == VK_SUCCESS);
//
//  // Acquire the swapchain image in order to set its layout
//  res = vkAcquireNextImageKHR(info.device, info.swap_chain, UINT64_MAX, imageAcquiredSemaphore, VK_NULL_HANDLE,
//                              &info.current_buffer);
//  assert(res >= 0);
//
//  // The initial layout for the color and depth attachments will be
//  // LAYOUT_UNDEFINED because at the start of the renderpass, we don't
//  // care about their contents. At the start of the subpass, the color
//  // attachment's layout will be transitioned to LAYOUT_COLOR_ATTACHMENT_OPTIMAL
//  // and the depth stencil attachment's layout will be transitioned to
//  // LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL.  At the end of the renderpass,
//  // the color attachment's layout will be transitioned to
//  // LAYOUT_PRESENT_SRC_KHR to be ready to present.  This is all done as part
//  // of the renderpass, no barriers are necessary.
//  VkAttachmentDescription attachments[2];
//  attachments[0].format = info.format;
//  attachments[0].samples = NUM_SAMPLES;
//  attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
//  attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
//  attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
//  attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//  attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
//  attachments[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
//  attachments[0].flags = 0;
//
//  attachments[1].format = info.depth.format;
//  attachments[1].samples = NUM_SAMPLES;
//  attachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
//  attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//  attachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
//  attachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//  attachments[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
//  attachments[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
//  attachments[1].flags = 0;
//
//  VkAttachmentReference color_reference = {};
//  color_reference.attachment = 0;
//  color_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
//
//  VkAttachmentReference depth_reference = {};
//  depth_reference.attachment = 1;
//  depth_reference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
//
//  VkSubpassDescription subpass = {};
//  subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
//  subpass.flags = 0;
//  subpass.inputAttachmentCount = 0;
//  subpass.pInputAttachments = NULL;
//  subpass.colorAttachmentCount = 1;
//  subpass.pColorAttachments = &color_reference;
//  subpass.pResolveAttachments = NULL;
//  subpass.pDepthStencilAttachment = &depth_reference;
//  subpass.preserveAttachmentCount = 0;
//  subpass.pPreserveAttachments = NULL;
//
//  VkRenderPassCreateInfo rp_info = {};
//  rp_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
//  rp_info.pNext = NULL;
//  rp_info.attachmentCount = 2;
//  rp_info.pAttachments = attachments;
//  rp_info.subpassCount = 1;
//  rp_info.pSubpasses = &subpass;
//  rp_info.dependencyCount = 0;
//  rp_info.pDependencies = NULL;
//
//  res = vkCreateRenderPass(info.device, &rp_info, NULL, &info.render_pass);
//  assert(res == VK_SUCCESS);
}

RenderPass::~RenderPass() {
//  vkDestroyRenderPass(info.device, info.render_pass, NULL);
//  vkDestroySemaphore(info.device, imageAcquiredSemaphore, NULL);
//  destroy_depth_buffer(info);
//  destroy_swap_chain(info);
}

} // namespace rwc