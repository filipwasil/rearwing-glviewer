/* Copyright (C) Filip Wasil, All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Filip Wasil <fillwave@gmail.com>
 */

#include <core/Shader.hpp>

namespace rwc {

Shader::Shader() {
//  static const char *vertShaderText =
//    "#version 400\n"
//    "#extension GL_ARB_separate_shader_objects : enable\n"
//    "#extension GL_ARB_shading_language_420pack : enable\n"
//    "layout (std140, binding = 0) uniform bufferVals {\n"
//    "    mat4 mvp;\n"
//    "} myBufferVals;\n"
//    "layout (location = 0) in vec4 pos;\n"
//    "layout (location = 1) in vec4 inColor;\n"
//    "layout (location = 0) out vec4 outColor;\n"
//    "void main() {\n"
//    "   outColor = inColor;\n"
//    "   gl_Position = myBufferVals.mvp * pos;\n"
//    "}\n";
//
//  static const char *fragShaderText =
//    "#version 400\n"
//    "#extension GL_ARB_separate_shader_objects : enable\n"
//    "#extension GL_ARB_shading_language_420pack : enable\n"
//    "layout (location = 0) in vec4 color;\n"
//    "layout (location = 0) out vec4 outColor;\n"
//    "void main() {\n"
//    "   outColor = color;\n"
//    "}\n";
//
//  std::vector<unsigned int> vtx_spv;
//  info.shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
//  info.shaderStages[0].pNext = NULL;
//  info.shaderStages[0].pSpecializationInfo = NULL;
//  info.shaderStages[0].flags = 0;
//  info.shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
//  info.shaderStages[0].pName = "main";
//
//  init_glslang();
//  retVal = GLSLtoSPV(VK_SHADER_STAGE_VERTEX_BIT, vertShaderText, vtx_spv);
//  assert(retVal);
//
//  VkShaderModuleCreateInfo moduleCreateInfo;
//  moduleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
//  moduleCreateInfo.pNext = NULL;
//  moduleCreateInfo.flags = 0;
//  moduleCreateInfo.codeSize = vtx_spv.size() * sizeof(unsigned int);
//  moduleCreateInfo.pCode = vtx_spv.data();
//  res = vkCreateShaderModule(info.device, &moduleCreateInfo, NULL, &info.shaderStages[0].module);
//  assert(res == VK_SUCCESS);
//
//  std::vector<unsigned int> frag_spv;
//  info.shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
//  info.shaderStages[1].pNext = NULL;
//  info.shaderStages[1].pSpecializationInfo = NULL;
//  info.shaderStages[1].flags = 0;
//  info.shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
//  info.shaderStages[1].pName = "main";
//
//  retVal = GLSLtoSPV(VK_SHADER_STAGE_FRAGMENT_BIT, fragShaderText, frag_spv);
//  assert(retVal);
//
//  moduleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
//  moduleCreateInfo.pNext = NULL;
//  moduleCreateInfo.flags = 0;
//  moduleCreateInfo.codeSize = frag_spv.size() * sizeof(unsigned int);
//  moduleCreateInfo.pCode = frag_spv.data();
//  res = vkCreateShaderModule(info.device, &moduleCreateInfo, NULL, &info.shaderStages[1].module);
//  assert(res == VK_SUCCESS);
//
//  finalize_glslang();
}

Shader::~Shader() {
//  vkDestroyShaderModule(info.device, info.shaderStages[0].module, NULL);
//  vkDestroyShaderModule(info.device, info.shaderStages[1].module, NULL);
}

} // namespace rwc