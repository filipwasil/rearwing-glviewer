#pragma once

#include <tuple>
#include <Math.hpp>

using VBODataDefault = std::tuple <glm::vec3, glm::vec2>;

static const std::array<VBODataDefault, 36> textured_cube_buffer {
  // left face
  VBODataDefault { { -1.0f, -1.0f, -1.0f } , { 1.f, 0.f } }, // lft-top-front
  VBODataDefault { { -1.0f, 1.0f, 1.0f } , { 0.f, 1.f } }, // lft-btm-back
  VBODataDefault { { -1.0f, -1.0f, 1.0f } , { 0.f, 0.f } }, // lft-top-back
  VBODataDefault { { -1.0f, 1.0f, 1.0f } , { 0.f, 1.f } }, // lft-btm-back
  VBODataDefault { { -1.0f, -1.0f, -1.0f } , { 1.f, 0.f } }, // lft-top-front
  VBODataDefault { { -1.0f, 1.0f, -1.0f } , { 1.f, 1.f } }, // lft-btm-front
  // front face
  VBODataDefault { { -1.0f, -1.0f, -1.0f } , { 0.f, 0.f } }, // lft-top-front
  VBODataDefault { { 1.0f, -1.0f, -1.0f } , { 1.f, 0.f } }, // rgt-top-front
  VBODataDefault { { 1.0f, 1.0f, -1.0f } , { 1.f, 1.f } }, // rgt-btm-front
  VBODataDefault { { -1.0f, -1.0f, -1.0f } , { 0.f, 0.f } }, // lft-top-front
  VBODataDefault { { 1.0f, 1.0f, -1.0f } , { 1.f, 1.f } }, // rgt-btm-front
  VBODataDefault { { -1.0f, 1.0f, -1.0f } , { 0.f, 1.f } }, // lft-btm-front
  // top face
  VBODataDefault { { -1.0f, -1.0f, -1.0f } , { 0.f, 1.f } }, // lft-top-front
  VBODataDefault { { 1.0f, -1.0f, 1.0f } , { 1.f, 0.f } }, // rgt-top-back
  VBODataDefault { { 1.0f, -1.0f, -1.0f } , { 1.f, 1.f } }, // rgt-top-front
  VBODataDefault { { -1.0f, -1.0f, -1.0f } , { 0.f, 1.f } }, // lft-top-front
  VBODataDefault { { -1.0f, -1.0f, 1.0f } , { 0.f, 0.f } }, // lft-top-back
  VBODataDefault { { 1.0f, -1.0f, 1.0f } , { 1.f, 0.f } }, // rgt-top-back
  // bottom face
  VBODataDefault { { -1.0f, 1.0f, -1.0f, } , { 0.f, 0.f } }, // lft-btm-front
  VBODataDefault { { 1.0f, 1.0f, 1.0f } , { 1.f, 1.f } }, // rgt-btm-back
  VBODataDefault { { -1.0f, 1.0f, 1.0f } , { 0.f, 1.f } }, // lft-btm-back
  VBODataDefault { { -1.0f, 1.0f, -1.0f } , { 0.f, 0.f } }, // lft-btm-front
  VBODataDefault { { 1.0f, 1.0f, -1.0f } , { 1.f, 0.f } }, // rgt-btm-front
  VBODataDefault { { 1.0f, 1.0f, 1.0f } , { 1.f, 1.f } }, // rgt-btm-back
  // right face
  VBODataDefault { { 1.0f, 1.0f, -1.0f } , { 0.f, 1.f } }, // rgt-btm-front
  VBODataDefault { { 1.0f, -1.0f, 1.0f } , { 1.f, 0.f } }, // rgt-top-back
  VBODataDefault { { 1.0f, 1.0f, 1.0f } , { 1.f, 1.f } }, // rgt-btm-back
  VBODataDefault { { 1.0f, -1.0f, 1.0f } , { 1.f, 0.f } }, // rgt-top-back
  VBODataDefault { { 1.0f, 1.0f, -1.0f } , { 0.f, 1.f } }, // rgt-btm-front
  VBODataDefault { { 1.0f, -1.0f, -1.0f } , { 0.f, 0.f } }, // rgt-top-front
  // back face
  VBODataDefault { { -1.0f, 1.0f, 1.0f } , { 1.f, 1.f } }, // lft-btm-back
  VBODataDefault { { 1.0f, 1.0f, 1.0f } , { 0.f, 1.f } }, // rgt-btm-back
  VBODataDefault { { -1.0f, -1.0f, 1.0f } , { 1.f, 0.f } }, // lft-top-back
  VBODataDefault { { -1.0f, -1.0f, 1.0f } , { 1.f, 0.f } }, // lft-top-back
  VBODataDefault { { 1.0f, 1.0f, 1.0f } , { 0.f, 1.f } }, // rgt-btm-back
  VBODataDefault { { 1.0f, -1.0f, 1.0f } , { 0.f, 0.f} }   // rgt-top-back
};