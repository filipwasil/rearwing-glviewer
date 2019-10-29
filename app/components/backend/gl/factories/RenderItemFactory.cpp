#include "RenderItemFactory.hpp"

#include "ConfigGL.hpp"
#include <Exception.hpp>

#include <loader_models_obj/loader_models_obj.h>
#include <loader_textures_etc/ETCTextureLoader.hpp>
#include <loader_textures_raw/TextureLoader.hpp>
#include "ProgramObjectFactory.hpp"
#include "../../Renderer.hpp"
#include "../../Uniform.hpp"
#include <istream>

namespace rwc
{

RenderItem RenderItemFactory::create(
    BufferObjectFactory::Shape shape
    , const char* pathVertexShader
    , const char* pathFragmentShader
    , const char* pathTexture
    , const glm::mat4& transformation)
{
    RenderItem node{};

    node.mVBO = BufferObjectFactory::create(shape, transformation);

    // Reserving space for 2 attributes
    // Each of the attributes will occupy 5 floats
    const size_t perVertexDataSizeInBytes = 5 * sizeof(float);
    node.mAttributes.reserve(2);
    node.mAttributes.push_back(RenderItem::Attribute {unsigned(0), int(3), GL_FLOAT, perVertexDataSizeInBytes, nullptr, false});
    node.mAttributes.push_back(RenderItem::Attribute {unsigned(1), int(2), GL_FLOAT, perVertexDataSizeInBytes, reinterpret_cast<void*>(3*sizeof(float)), false});

    node.mDrawType = GL_TRIANGLES;

    node.mPO = ProgramObjectFactory::load(pathFragmentShader, pathVertexShader);

    node.mTextures.push_back(RenderItem::Texture{DIFFUSE_TEXTURE_UNIT, TextureLoader().load(pathTexture)});

    validateAttributes(node);
    initActiveUniforms(node);

    return node;
}

RenderItem RenderItemFactory::create(
    BufferObjectFactory::Shape shape
    , const char* pathProgramBinary
    , const char* pathTexture
    , const glm::mat4& transformation)
{
    RenderItem node{};

    node.mVBO = BufferObjectFactory::create(shape, transformation);

    // Reserving space for 3 attributes
    // Each of the attributes will occupy 5 floats
    const size_t perVertexDataSizeInBytes = 5 * sizeof(float);
    node.mAttributes.reserve(3);
    node.mAttributes.push_back(RenderItem::Attribute {unsigned(0), int(3), GL_FLOAT, perVertexDataSizeInBytes, nullptr, false});
    node.mAttributes.push_back(RenderItem::Attribute {unsigned(1), int(2), GL_FLOAT, perVertexDataSizeInBytes, reinterpret_cast<void*>(3*sizeof(float)), false});

    node.mDrawType = GL_TRIANGLES;

    node.mPO = ProgramObjectFactory::load(pathProgramBinary);

    node.mTextures.push_back(RenderItem::Texture{DIFFUSE_TEXTURE_UNIT, TextureLoader().load(pathTexture)});

    validateAttributes(node);
    initActiveUniforms(node);

    return node;
}


std::vector<RenderItem> RenderItemFactory::create(
    const char* path
    , const char* pathVertexShader
    , const char* pathFragmentShader
    , const char* pathTexture)
{
    auto nodes = create(path, ProgramObjectFactory::load(pathFragmentShader, pathVertexShader));

    for (auto& node : nodes)
    {
        node.mTextures.push_back(RenderItem::Texture{DIFFUSE_TEXTURE_UNIT, TextureLoader().load(pathTexture)});
        validateAttributes(node);
        initActiveUniforms(node);
    }
    return nodes;
}

std::vector<RenderItem> RenderItemFactory::create(
    const char* path
    , const char* pathProgramBinary
    , const char* pathTexture)
{
    auto nodes = create(path, ProgramObjectFactory::load(pathProgramBinary));
    for (auto& node : nodes)
    {
        node.mTextures.push_back(RenderItem::Texture{DIFFUSE_TEXTURE_UNIT, TextureLoader().load(pathTexture)});
        validateAttributes(node);
        initActiveUniforms(node);
    }
    return nodes;
}

std::vector<RenderItem> RenderItemFactory::create(const char* path, unsigned programId)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);
    if (!err.empty()) {
        throw Exception {err.c_str(), LOCATION };
    }

    if (!ret) {
        throw Exception {"Failed to read file with model", LOCATION };
    }

    const bool isVertices = !attrib.vertices.empty();
    if (!isVertices) {
        throw Exception {"No vertices found for model. Corrupted file.", LOCATION };
    }

    std::vector<RenderItem> nodes;

    for (size_t s = 0; s < shapes.size(); ++s)
    {
        RenderItem node;
        std::vector<float> vbo;

        size_t index_offset = 0;
        const size_t verticesInTriangle = 3;
        const size_t floatsInSingleDataStructure = 8;
        const auto facesInShape = shapes[s].mesh.num_face_vertices.size();
        vbo.reserve(facesInShape * verticesInTriangle * floatsInSingleDataStructure);
        for (size_t f = 0; f < facesInShape; ++f)
        {
            auto fv = shapes[s].mesh.num_face_vertices[f];
            for (size_t v = 0; v < fv; ++v)
            {
                tinyobj::index_t idx = shapes[s].mesh.indices[ index_offset + v ];
                const auto vertexIdx = 3 * idx.vertex_index;
                const auto normalIdx = 3 * idx.normal_index;
                vbo.push_back(attrib.vertices[ vertexIdx + 0] );
                vbo.push_back(attrib.vertices[ vertexIdx + 1] );
                vbo.push_back(attrib.vertices[ vertexIdx + 2] );
                vbo.push_back(attrib.normals[ normalIdx + 0] );
                vbo.push_back(attrib.normals[ normalIdx + 1] );
                vbo.push_back(attrib.normals[ normalIdx + 2] );
                vbo.push_back(attrib.texcoords[ 2 * idx.texcoord_index + 0] );
                vbo.push_back(1.0f - attrib.texcoords[ 2 * idx.texcoord_index + 1] );
            }
            index_offset += fv;

            shapes[s].mesh.material_ids[f];
        }

        glGenBuffers(1, &node.mVBO.mName);
        glBindBuffer(GL_ARRAY_BUFFER, node.mVBO.mName);
        glBufferData(GL_ARRAY_BUFFER, vbo.size() * sizeof(float), vbo.data(), GL_STATIC_DRAW);

        node.mVBO.mElements = vbo.size() / 8;
        node.mPO = programId;
        node.mAttributes.reserve(3);
        const size_t perVertexDataSizeInBytes = 8 * sizeof(float);
        node.mAttributes.push_back(RenderItem::Attribute {unsigned(0), int(3), GL_FLOAT, perVertexDataSizeInBytes, nullptr, false});
        node.mAttributes.push_back(RenderItem::Attribute {unsigned(1), int(3), GL_FLOAT, perVertexDataSizeInBytes, reinterpret_cast<void*>(3*sizeof(float)), false});
        node.mAttributes.push_back(RenderItem::Attribute {unsigned(2), int(2), GL_FLOAT, perVertexDataSizeInBytes, reinterpret_cast<void*>(6*sizeof(float)), false});

        node.mDrawType = GL_TRIANGLES;

        nodes.push_back(node);
    }

    return nodes;
}

void RenderItemFactory::validateAttributes(RenderItem& renderItem)
{
    int howMany = -1;
    glGetProgramiv(renderItem.mPO, GL_ACTIVE_ATTRIBUTES, &howMany);
    std::vector<int> activeLocations;
    activeLocations.reserve(howMany);
    constexpr size_t localBufferSize = 200;
    constexpr size_t localBufferMaxChars = localBufferSize - 1;
    for (int i = 0; i < howMany; ++i)
    {
        int name_len = -1;
        int num = -1;
        GLenum type = GL_ZERO;
        char name[localBufferSize];
        glGetActiveAttrib(renderItem.mPO, GLuint(i), localBufferMaxChars, &name_len, &num, &type, name);
        name[name_len] = 0;
        activeLocations.push_back(glGetAttribLocation(renderItem.mPO, name));
    }

    for (const auto location : activeLocations)
    {
        renderItem.mAttributes[location].active = true;
    }
}

RenderItem RenderItemFactory::createTextRenderItem(
    const char* pathFontMetadata
    , const char* pathFontAtlas
    , const char* pathToProgramBinary
    , const std::string& text
    , const vec3f& position
    , float fontSize
    , Text::Alignment alignment
    , const vec2f& screenResolution)
{
    RenderItem node{};

    node.mVBO = BufferObjectFactory::createTextBuffers(pathFontMetadata, text, position, fontSize, screenResolution, alignment);

    node.mDrawType = GL_TRIANGLES;

    node.mPO = ProgramObjectFactory::load(pathToProgramBinary);
    const size_t perVertexDataSizeInBytes = 5 * sizeof(float);
    node.mAttributes.push_back(RenderItem::Attribute {unsigned(0), int(3), GL_FLOAT, perVertexDataSizeInBytes, nullptr, false});
    node.mAttributes.push_back(RenderItem::Attribute {unsigned(1), int(2), GL_FLOAT, perVertexDataSizeInBytes, reinterpret_cast<void*>(3*sizeof(float)), false});
    validateAttributes(node);
    initActiveUniforms(node);

    node.mTextures.push_back(RenderItem::Texture{DIFFUSE_TEXTURE_UNIT, TextureLoader().load(pathFontAtlas)});

    return node;
}

RenderItem RenderItemFactory::createBackgroundRenderItem(const char* pathToProgramBinary)
{
    RenderItem node{};

    node.mPO = ProgramObjectFactory::load(pathToProgramBinary);

    node.mVBO = BufferObjectFactory::create(BufferObjectFactory::Shape::rectangle);
    const size_t perVertexDataSizeInBytes = 5 * sizeof(float);
    node.mAttributes.push_back(RenderItem::Attribute {unsigned(0), int(3), GL_FLOAT, perVertexDataSizeInBytes, nullptr, false});
    node.mAttributes.push_back(RenderItem::Attribute {unsigned(1), int(2), GL_FLOAT, perVertexDataSizeInBytes, reinterpret_cast<void*>(3*sizeof(float)), false});
    validateAttributes(node);
    initActiveUniforms(node);

    node.mDrawType = GL_TRIANGLES;

    return node;
}

RenderItem RenderItemFactory::createBackgroundRenderItem(const char* pathToVertexShader, const char* pathToFragmentShader)
{
    RenderItem node{};

    node.mPO = ProgramObjectFactory::load(pathToFragmentShader, pathToVertexShader);

    node.mVBO = BufferObjectFactory::create(BufferObjectFactory::Shape::rectangle);
    const size_t perVertexDataSizeInBytes = 5 * sizeof(float);
    node.mAttributes.push_back(RenderItem::Attribute {unsigned(0), int(3), GL_FLOAT, perVertexDataSizeInBytes, nullptr, false});
    node.mAttributes.push_back(RenderItem::Attribute {unsigned(1), int(2), GL_FLOAT, perVertexDataSizeInBytes, reinterpret_cast<void*>(3*sizeof(float)), false});
    validateAttributes(node);
    initActiveUniforms(node);

    node.mDrawType = GL_TRIANGLES;

    return node;
}

RenderItem RenderItemFactory::createTextRenderItem(
    const char* pathFontMetadata
    , const char* pathFontAtlas
    , const char* pathToVertexShader
    , const char* pathToFragmentShader
    , const std::string& text
    , const vec3f& position
    , float fontSize
    , Text::Alignment alignment
    , const vec2f& screenResolution)
{
    RenderItem node{};

    node.mVBO = BufferObjectFactory::createTextBuffers(pathFontMetadata, text, position, fontSize, screenResolution, alignment);

    node.mDrawType = GL_TRIANGLES;

    node.mPO = ProgramObjectFactory::load(pathToFragmentShader, pathToVertexShader);

    const size_t perVertexDataSizeInBytes = 5 * sizeof(float);
    node.mAttributes.push_back(RenderItem::Attribute {unsigned(0), int(3), GL_FLOAT, perVertexDataSizeInBytes, nullptr, false});
    node.mAttributes.push_back(RenderItem::Attribute {unsigned(1), int(2), GL_FLOAT, perVertexDataSizeInBytes, reinterpret_cast<void*>(3*sizeof(float)), false});

    validateAttributes(node);
    initActiveUniforms(node);

    node.mTextures.push_back(RenderItem::Texture{DIFFUSE_TEXTURE_UNIT, TextureLoader().load(pathFontAtlas)});

    return node;
}

void RenderItemFactory::initActiveUniforms(RenderItem& renderItem)
{
    GLint count{0};
    glGetProgramiv(renderItem.mPO, GL_ACTIVE_UNIFORMS, &count);

    if (count < 1)
    {
        return;
    }

    for (GLint i = 0; i < count; ++i)
    {
        GLint name_len = -1;
        GLint num = -1;
        GLenum type = GL_ZERO;
        constexpr size_t nameMaxSize = 100;
        constexpr size_t nameMaxChars = nameMaxSize - 1;
        char name_buffer[nameMaxSize];
        glGetActiveUniform(renderItem.mPO, GLuint(i), nameMaxChars, &name_len, &num, &type, name_buffer);
        name_buffer[name_len] = 0;
        GLint location = glGetUniformLocation(renderItem.mPO, name_buffer);
        renderItem.mUniforms.insert_or_assign(name_buffer, Uniform{type, num, location});
    }
}

} // namespace rwc
