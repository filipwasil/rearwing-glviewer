/* Copyright (C) Filip Wasil, All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Filip Wasil <fillwave@gmail.com>
 */

#include <core/Pipeline.hpp>

namespace rwc {

Pipeline::Pipeline() {
//  VkDynamicState dynamicStateEnables[VK_DYNAMIC_STATE_RANGE_SIZE];
//  VkPipelineDynamicStateCreateInfo dynamicState = {};
//  memset(dynamicStateEnables, 0, sizeof dynamicStateEnables);
//  dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
//  dynamicState.pNext = NULL;
//  dynamicState.pDynamicStates = dynamicStateEnables;
//  dynamicState.dynamicStateCount = 0;
//
//  VkPipelineVertexInputStateCreateInfo vi;
//  vi.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
//  vi.pNext = NULL;
//  vi.flags = 0;
//  vi.vertexBindingDescriptionCount = 1;
//  vi.pVertexBindingDescriptions = &info.vi_binding;
//  vi.vertexAttributeDescriptionCount = 2;
//  vi.pVertexAttributeDescriptions = info.vi_attribs;
//
//  VkPipelineInputAssemblyStateCreateInfo ia;
//  ia.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
//  ia.pNext = NULL;
//  ia.flags = 0;
//  ia.primitiveRestartEnable = VK_FALSE;
//  ia.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
//
//  VkPipelineRasterizationStateCreateInfo rs;
//  rs.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
//  rs.pNext = NULL;
//  rs.flags = 0;
//  rs.polygonMode = VK_POLYGON_MODE_FILL;
//  rs.cullMode = VK_CULL_MODE_BACK_BIT;
//  rs.frontFace = VK_FRONT_FACE_CLOCKWISE;
//  rs.depthClampEnable = VK_FALSE;
//  rs.rasterizerDiscardEnable = VK_FALSE;
//  rs.depthBiasEnable = VK_FALSE;
//  rs.depthBiasConstantFactor = 0;
//  rs.depthBiasClamp = 0;
//  rs.depthBiasSlopeFactor = 0;
//  rs.lineWidth = 1.0f;
//
//  VkPipelineColorBlendStateCreateInfo cb;
//  cb.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
//  cb.pNext = NULL;
//  cb.flags = 0;
//  VkPipelineColorBlendAttachmentState att_state[1];
//  att_state[0].colorWriteMask = 0xf;
//  att_state[0].blendEnable = VK_FALSE;
//  att_state[0].alphaBlendOp = VK_BLEND_OP_ADD;
//  att_state[0].colorBlendOp = VK_BLEND_OP_ADD;
//  att_state[0].srcColorBlendFactor = VK_BLEND_FACTOR_ZERO;
//  att_state[0].dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
//  att_state[0].srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
//  att_state[0].dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
//  cb.attachmentCount = 1;
//  cb.pAttachments = att_state;
//  cb.logicOpEnable = VK_FALSE;
//  cb.logicOp = VK_LOGIC_OP_NO_OP;
//  cb.blendConstants[0] = 1.0f;
//  cb.blendConstants[1] = 1.0f;
//  cb.blendConstants[2] = 1.0f;
//  cb.blendConstants[3] = 1.0f;
//
//  VkPipelineViewportStateCreateInfo vp = {};
//  vp.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
//  vp.pNext = NULL;
//  vp.flags = 0;
//  vp.viewportCount = NUM_VIEWPORTS;
//  dynamicStateEnables[dynamicState.dynamicStateCount++] = VK_DYNAMIC_STATE_VIEWPORT;
//  vp.scissorCount = NUM_SCISSORS;
//  dynamicStateEnables[dynamicState.dynamicStateCount++] = VK_DYNAMIC_STATE_SCISSOR;
//  vp.pScissors = NULL;
//  vp.pViewports = NULL;
//
//  VkPipelineDepthStencilStateCreateInfo ds;
//  ds.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
//  ds.pNext = NULL;
//  ds.flags = 0;
//  ds.depthTestEnable = VK_TRUE;
//  ds.depthWriteEnable = VK_TRUE;
//  ds.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
//  ds.depthBoundsTestEnable = VK_FALSE;
//  ds.minDepthBounds = 0;
//  ds.maxDepthBounds = 0;
//  ds.stencilTestEnable = VK_FALSE;
//  ds.back.failOp = VK_STENCIL_OP_KEEP;
//  ds.back.passOp = VK_STENCIL_OP_KEEP;
//  ds.back.compareOp = VK_COMPARE_OP_ALWAYS;
//  ds.back.compareMask = 0;
//  ds.back.reference = 0;
//  ds.back.depthFailOp = VK_STENCIL_OP_KEEP;
//  ds.back.writeMask = 0;
//  ds.front = ds.back;
//
//  VkPipelineMultisampleStateCreateInfo ms;
//  ms.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
//  ms.pNext = NULL;
//  ms.flags = 0;
//  ms.pSampleMask = NULL;
//  ms.rasterizationSamples = NUM_SAMPLES;
//  ms.sampleShadingEnable = VK_FALSE;
//  ms.alphaToCoverageEnable = VK_FALSE;
//  ms.alphaToOneEnable = VK_FALSE;
//  ms.minSampleShading = 0.0;
//
//  VkGraphicsPipelineCreateInfo pipeline;
//  pipeline.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
//  pipeline.pNext = NULL;
//  pipeline.layout = info.pipeline_layout;
//  pipeline.basePipelineHandle = VK_NULL_HANDLE;
//  pipeline.basePipelineIndex = 0;
//  pipeline.flags = 0;
//  pipeline.pVertexInputState = &vi;
//  pipeline.pInputAssemblyState = &ia;
//  pipeline.pRasterizationState = &rs;
//  pipeline.pColorBlendState = &cb;
//  pipeline.pTessellationState = NULL;
//  pipeline.pMultisampleState = &ms;
//  pipeline.pDynamicState = &dynamicState;
//  pipeline.pViewportState = &vp;
//  pipeline.pDepthStencilState = &ds;
//  pipeline.pStages = info.shaderStages;
//  pipeline.stageCount = 2;
//  pipeline.renderPass = info.render_pass;
//  pipeline.subpass = 0;
//
//  res = vkCreateGraphicsPipelines(info.device, VK_NULL_HANDLE, 1, &pipeline, NULL, &info.pipeline);
//  assert(res == VK_SUCCESS);
//  execute_end_command_buffer(info);
//  execute_queue_command_buffer(info);
}

Pipeline::~Pipeline() {
//  vkDestroyPipeline(info.device, info.pipeline, NULL);
//  destroy_descriptor_pool(info);
//  destroy_vertex_buffer(info);
//  destroy_framebuffers(info);
//  destroy_shaders(info);
//  destroy_renderpass(info);
//  destroy_descriptor_and_pipeline_layouts(info);
//  destroy_uniform_buffer(info);
//  destroy_depth_buffer(info);
//  destroy_swap_chain(info);
//  destroy_command_buffer(info);
//  destroy_command_pool(info);
}

} // namespace rwc