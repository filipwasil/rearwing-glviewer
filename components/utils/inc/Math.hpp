#pragma once

#include <array>

#define GLM_FORCE_RADIANS

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace rwc
{
    using vec2f = std::array<float, 2>;
    using vec3f = std::array<float, 3>;
    using vec4f = std::array<float, 4>;
    using vec5f = std::array<float, 5>;

glm::mat4 getMVP(unsigned int width, unsigned int height);

} // namespace rwc
