#include "../../RenderItem.hpp"
#include <ConfigGL.hpp>
#include <Exception.hpp>

namespace rwc
{
void RenderItem::render() const
{
    // Textures
    for (const auto& texture : mTextures)
    {
        glActiveTexture(texture.mUnit);
        glBindTexture(GL_TEXTURE_2D, texture.mName);
    }

    // Programs
    glUseProgram(mPO);

    // Buffers
    if (mVAO.mActive)
    {
        glBindVertexArray(mVAO.mName);
    }
    else
    {
        if (0 != mIBO.mElements)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO.mName);
        }
        glBindBuffer(GL_ARRAY_BUFFER, mVBO.mName);

        // Attributes
        for (const auto& attribute : mAttributes)
        {
            if (!attribute.active)
            {
                continue;
            }
            glVertexAttribPointer(attribute.location, attribute.count, attribute.type, GL_FALSE, attribute.size, attribute.offset);
            glEnableVertexAttribArray(attribute.location);
        }
    }

    // draws
    if (0 == mIBO.mElements)
    {
        glDrawArrays(mDrawType, 0, mVBO.mElements);
    }
    else
    {
        glDrawElements(mDrawType, mIBO.mElements, GL_UNSIGNED_INT, nullptr);
    }

    if (mVAO.mActive)
    {
        return;
    }

    for (const auto& attribute : mAttributes)
    {
        if (!attribute.active)
        {
            continue;
        }
        glDisableVertexAttribArray(attribute.location);
    }
}

const RenderItem& RenderItem::useProgramObject() const
{
    glUseProgram(mPO);
    return *this;
}

const RenderItem& RenderItem::pushUniform(const std::string& name, GLint data) const
{
    const auto uniform = mUniforms.find(name);
    if (uniform == mUniforms.end())
    {
        throw Exception {"Uniform: " + name + " failed to push", LOCATION };
    }
    uniform->second.push(data);
    return *this;
}

const RenderItem& RenderItem::pushUniform(const std::string& name, GLint* data, GLint count) const
{
    const auto uniform = mUniforms.find(name);
    if (uniform == mUniforms.end())
    {
        throw Exception {"Uniform: " + name + " failed to push", LOCATION };
    }
    uniform->second.push(data, count);
    return *this;
}

const RenderItem& RenderItem::pushUniform(const std::string& name, GLfloat data) const
{
    const auto uniform = mUniforms.find(name);
    if (uniform == mUniforms.end())
    {
        throw Exception {"Uniform: " + name + " failed to push", LOCATION };
    }
    uniform->second.push(data);
    return *this;
}

const RenderItem& RenderItem::pushUniform(const std::string& name, GLfloat* data, GLint count) const
{
    const auto uniform = mUniforms.find(name);
    if (uniform == mUniforms.end())
    {
        throw Exception {"Uniform: " + name + " failed to push", LOCATION };
    }
    uniform->second.push(data, count);
    return *this;
}

const RenderItem& RenderItem::pushUniform(const std::string& name, const glm::mat3& data) const
{
    const auto uniform = mUniforms.find(name);
    if (uniform == mUniforms.end())
    {
        throw Exception {"Uniform: " + name + " failed to push", LOCATION };
    }
    uniform->second.push(data);
    return *this;
}

const RenderItem& RenderItem::pushUniform(const std::string& name, const glm::mat4& data) const
{
    const auto uniform = mUniforms.find(name);
    if (uniform == mUniforms.end())
    {
        throw Exception {"Uniform: " + name + " failed to push", LOCATION };
    }
    uniform->second.push(data);
    return *this;
}

const RenderItem& RenderItem::pushUniform(const std::string& name, glm::mat4* data, int count) const
{
    const auto uniform = mUniforms.find(name);
    if (uniform == mUniforms.end())
    {
        throw Exception {"Uniform: " + name + " failed to push", LOCATION };
    }
    uniform->second.push(data, count);
    return *this;
}

const RenderItem& RenderItem::pushUniform(const std::string& name, const glm::vec2& data) const
{
    const auto uniform = mUniforms.find(name);
    if (uniform == mUniforms.end())
    {
        throw Exception {"Uniform: " + name + " failed to push", LOCATION };
    }
    uniform->second.push(data);
    return *this;
}

const RenderItem& RenderItem::pushUniform(const std::string& name, const glm::vec3& data) const
{
    const auto uniform = mUniforms.find(name);
    if (uniform == mUniforms.end())
    {
        throw Exception {"Uniform: " + name + " failed to push", LOCATION };
    }
    uniform->second.push(data);
    return *this;
}

const RenderItem& RenderItem::pushUniform(const std::string& name, const vec3f& data) const
{
    const auto uniform = mUniforms.find(name);
    if (uniform == mUniforms.end())
    {
        throw Exception {"Uniform: " + name + " failed to push", LOCATION };
    }
    uniform->second.push(data);
    return *this;
}

const RenderItem& RenderItem::pushUniform(const std::string& name, const vec2f& data) const
{
    const auto uniform = mUniforms.find(name);
    if (uniform == mUniforms.end())
    {
        throw Exception {"Uniform: " + name + " failed to push", LOCATION };
    }
    uniform->second.push(data);
    return *this;
}

const RenderItem& RenderItem::pushUniform(const std::string& name, glm::vec3* data, int count) const
{
    const auto uniform = mUniforms.find(name);
    if (uniform == mUniforms.end())
    {
        throw Exception {"Uniform: " + name + " failed to push", LOCATION };
    }
    uniform->second.push(data, count);
    return *this;
}

const RenderItem& RenderItem::pushUniform(const std::string& name, const glm::vec4& data) const
{
    const auto uniform = mUniforms.find(name);
    if (uniform == mUniforms.end())
    {
        throw Exception {"Uniform: " + name + " failed to push", LOCATION };
    }
    uniform->second.push(data);
    return *this;
}

const RenderItem& RenderItem::pushUniform(const std::string& name, const vec4f& data) const
{
    const auto uniform = mUniforms.find(name);
    if (uniform == mUniforms.end())
    {
        throw Exception {"Uniform: " + name + " failed to push", LOCATION };
    }
    uniform->second.push(data);
    return *this;
}

} // namespace rwc