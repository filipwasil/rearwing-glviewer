/* Copyright (C) Filip Wasil, All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Filip Wasil <fillwave@gmail.com>
 */

#include <core/PipelineLayout.hpp>

namespace rwc {

PipelineLayout::PipelineLayout() {
//  /* Start with just our uniform buffer that has our transformation matrices
//   * (for the vertex shader). The fragment shader we intend to use needs no
//   * external resources, so nothing else is necessary
//   */
//
//  /* Note that when we start using textures, this is where our sampler will
//   * need to be specified
//   */
//  VkDescriptorSetLayoutBinding layout_binding = {};
//  layout_binding.binding = 0;
//  layout_binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//  layout_binding.descriptorCount = 1;
//  layout_binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
//  layout_binding.pImmutableSamplers = NULL;
//
//  /* Next take layout bindings and use them to create a descriptor set layout
//   */
//  VkDescriptorSetLayoutCreateInfo descriptor_layout = {};
//  descriptor_layout.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
//  descriptor_layout.pNext = NULL;
//  descriptor_layout.bindingCount = 1;
//  descriptor_layout.pBindings = &layout_binding;
//
//  info.desc_layout.resize(NUM_DESCRIPTOR_SETS);
//  res = vkCreateDescriptorSetLayout(info.device, &descriptor_layout, NULL, info.desc_layout.data());
//  assert(res == VK_SUCCESS);
//
//  /* Now use the descriptor layout to create a pipeline layout */
//  VkPipelineLayoutCreateInfo pPipelineLayoutCreateInfo = {};
//  pPipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
//  pPipelineLayoutCreateInfo.pNext = NULL;
//  pPipelineLayoutCreateInfo.pushConstantRangeCount = 0;
//  pPipelineLayoutCreateInfo.pPushConstantRanges = NULL;
//  pPipelineLayoutCreateInfo.setLayoutCount = NUM_DESCRIPTOR_SETS;
//  pPipelineLayoutCreateInfo.pSetLayouts = info.desc_layout.data();
//
//  res = vkCreatePipelineLayout(info.device, &pPipelineLayoutCreateInfo, NULL, &info.pipeline_layout);
//  assert(res == VK_SUCCESS);
}

PipelineLayout::~PipelineLayout() {
//  for (int i = 0; i < NUM_DESCRIPTOR_SETS; i++) vkDestroyDescriptorSetLayout(info.device, info.desc_layout[i], NULL);
//  vkDestroyPipelineLayout(info.device, info.pipeline_layout, NULL);
}

} // namespace rwc