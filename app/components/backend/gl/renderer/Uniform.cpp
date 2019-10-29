#include "../../Uniform.hpp"
#include <ConfigGL.hpp>

namespace rwc
{

void Uniform::push(int value) const
{
    glUniform1i(mLocation, value);
}

void Uniform::push(GLint* value, int count) const
{
    glUniform1iv(mLocation, count, value);
}

void Uniform::push(GLfloat value) const
{
    glUniform1f(mLocation, value);
}

void Uniform::push(GLfloat* value, GLint count) const
{
    glUniform1fv(mLocation, count, value);
}

void Uniform::push(const glm::vec2& value) const
{
    glUniform2fv(mLocation, 1, glm::value_ptr(value));
}

void Uniform::push(const glm::vec3& value) const
{
    glUniform3fv(mLocation, 1, glm::value_ptr(value));
}

void Uniform::push(const vec3f& value) const
{
    glUniform3fv(mLocation, 1, value.data());
}

void Uniform::push(const vec2f& value) const
{
    glUniform2fv(mLocation, 1, value.data());
}

void Uniform::push(const glm::vec4& value) const
{
    glUniform4fv(mLocation, 1, glm::value_ptr(value));
}

void Uniform::push(const vec4f& value) const
{
    glUniform4fv(mLocation, 1, value.data());
}

void Uniform::push(const glm::mat2& value) const
{
    glUniformMatrix2fv(mLocation, 1, GL_FALSE, glm::value_ptr(value));
}

void Uniform::push(const glm::mat3& value) const
{
    glUniformMatrix3fv(mLocation, 1, GL_FALSE, glm::value_ptr(value));
}

void Uniform::push(const glm::mat4& value) const
{
    glUniformMatrix4fv(mLocation, 1, GL_FALSE, glm::value_ptr(value));
}

void Uniform::push(glm::vec3* value, int count) const
{
    glUniform3fv(mLocation, count, reinterpret_cast<GLfloat*>(value));
}

void Uniform::push(glm::mat4* value, int count) const
{
    glUniformMatrix4fv(mLocation, count, GL_FALSE, reinterpret_cast<GLfloat*>(value));
}

} // namespace rwc