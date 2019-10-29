#pragma once

#include <Math.hpp>

#include <string>

namespace rwc
{
/*!
 * @struct OpenGL Uniform data
 *
 */
struct Uniform final
{
/*!
 * @brief Push functions with various types
 *        Each function represents different OpenGL call
 *
 */
  void push(int value) const;
  void push(int* value, int size) const;
  void push(float value) const;
  void push(float* value, int size) const;
  void push(const glm::mat4& value) const;
  void push(glm::mat4* value, int size) const;
  void push(const glm::mat3& value) const;
  void push(const glm::mat2& value) const;
  void push(const glm::vec2& value) const;
  void push(const glm::vec3& value) const;
  void push(const vec3f& value) const;
  void push(const vec2f& value) const;
  void push(glm::vec3* value, int size) const;
  void push(const glm::vec4& value) const;
  void push(const vec4f& value) const;

  unsigned mType{0};
  int mSize{0};
  int mLocation{-1};
};

} // namespace rwc

