#include "BufferObjectFactory.hpp"

#include <Exception.hpp>
#include "FontFactory.hpp"
#include <ConfigGL.hpp>
#include <Math.hpp>

namespace
{

using VertexData = rwc::vec5f;

static std::array<VertexData, 6> rectangle =
  {
    -1.0f, 1.0f, 0.0f, 0.0f, 0.0f
    ,1.0f, -1.0f, 0.0f, 1.0f, 1.0f
    ,-1.0f, -1.0f, 0.0f, 0.0f, 1.0f
    ,1.0f, -1.0f, 0.0f, 1.0f, 1.0f
    ,-1.0f, 1.0f, 0.0f, 0.0f, 0.0f
    ,1.0f, 1.0f, 0.0f, 1.0f, 0.0f
  };
}

namespace rwc
{

RenderItem::Buffer BufferObjectFactory::create(Shape shape, const glm::mat4& transformation)
{
  unsigned name{};
  glGenBuffers(1, &name);
  glBindBuffer(GL_ARRAY_BUFFER, name);

  const auto bytesPerVertex = VertexData().size() * sizeof(float);

  if (transformation == glm::mat4(1.0))
  {
    switch(shape)
    {
      case Shape::rectangle:
        glBufferData(GL_ARRAY_BUFFER, rectangle.size() * bytesPerVertex, rectangle.data(), GL_STATIC_DRAW);
        return {rectangle.size(), name};
      default:
        throw Exception {"Unhandled shape requested", LOCATION};
    }
  }
  std::vector<VertexData> transformedVertices{rectangle.begin(), rectangle.end()};
  const GLint verticesCount = transformedVertices.size();
  for (GLint it = 0; it < verticesCount; ++it)
  {
    glm::vec4 v = transformation * glm::vec4(rectangle[it][0], rectangle[it][1], rectangle[it][2], 1.0);
    transformedVertices[it][0] = v[0];
    transformedVertices[it][1] = v[1];
    transformedVertices[it][2] = v[2];
  }
  glBufferData(GL_ARRAY_BUFFER, verticesCount * bytesPerVertex, transformedVertices.data(), GL_STATIC_DRAW);
  return {verticesCount, name};
}

RenderItem::Buffer BufferObjectFactory::createTextBuffers(
  const char* pathFontMetadata
  , const std::string& text
  , const vec3f& position
  , float fontSize
  , const vec2f& screenResolution
  , Text::Alignment alignment)
{
  RenderItem::Buffer buffer{};
  glGenBuffers(1, &buffer.mName);

  BufferObjectFactory::updateTextBuffers(buffer, FontFactory::create(pathFontMetadata), text, position, fontSize, screenResolution, alignment);
  return buffer;
}

void BufferObjectFactory::updateTextBuffers(
  RenderItem::Buffer& buffer
  , const Text::Font& font
  , const std::string& text
  , const vec3f& position
  , float fontSize
  , const vec2f& screenResolution
  , Text::Alignment alignment)
{
  const int length = text.length();
  std::vector<GLfloat> pointsTmp;
  std::vector<GLfloat> texcoordsTmp;

  const size_t verticesForWholeText = length * 12;
  pointsTmp.reserve(verticesForWholeText);
  texcoordsTmp.reserve(verticesForWholeText);

  float charPosX = position[0];
  for (int i = 0; i < length; ++i)
  {
    const int asciiCode = text[i];

    const int atlasColumn = (asciiCode - ' ') % font.atlasColumns;
    const int atlasRow = (asciiCode - ' ') / font.atlasColumns;

    const float singleCharSpaceInAtlas[2] = {
      1.0f / font.atlasRows
      , 1.0f / font.atlasColumns
    };

    const float s = atlasColumn * singleCharSpaceInAtlas[1];
    const float t = (atlasRow + 1) * singleCharSpaceInAtlas[0];

    const float xPos = charPosX;
    const float yPos = position[1] - fontSize / screenResolution[1] * font.offsets[asciiCode];

    const float positionOffsets[2] = {
      fontSize / screenResolution[0]
      , fontSize / screenResolution[1]
    };

    const float textureCoordinatesOffsets[2] = {
      t - singleCharSpaceInAtlas[0]
      , s + singleCharSpaceInAtlas[1]
    };

    pointsTmp.push_back(xPos);
    pointsTmp.push_back(yPos);

    pointsTmp.push_back(xPos + positionOffsets[0]);
    pointsTmp.push_back(yPos - positionOffsets[1]);

    pointsTmp.push_back(xPos);
    pointsTmp.push_back(yPos - positionOffsets[1]);

    pointsTmp.push_back(xPos + positionOffsets[0]);
    pointsTmp.push_back(yPos - positionOffsets[1]);

    pointsTmp.push_back(xPos);
    pointsTmp.push_back(yPos);

    pointsTmp.push_back(xPos + positionOffsets[0]);
    pointsTmp.push_back(yPos);

    texcoordsTmp.push_back(s);
    texcoordsTmp.push_back(textureCoordinatesOffsets[0]);

    texcoordsTmp.push_back(textureCoordinatesOffsets[1]);
    texcoordsTmp.push_back(t);

    texcoordsTmp.push_back(s);
    texcoordsTmp.push_back(t);

    texcoordsTmp.push_back(textureCoordinatesOffsets[1]);
    texcoordsTmp.push_back(t);

    texcoordsTmp.push_back(s);
    texcoordsTmp.push_back(textureCoordinatesOffsets[0]);

    texcoordsTmp.push_back(textureCoordinatesOffsets[1]);
    texcoordsTmp.push_back(textureCoordinatesOffsets[0]);

    if (i + 1 < length)
    {
      charPosX += font.widths[asciiCode] * fontSize / screenResolution[0];
    }
  }

  const size_t size = pointsTmp.size();
  if (size != texcoordsTmp.size())
  {
    throw Exception {"Corrupted data inside the font metadata file", LOCATION };
  }

  using Vertex = std::array<float, 5>;
  std::vector<Vertex> vertices{};
  const size_t verticesCount = size / 2;

  Vertex vertex;
  vertices.reserve(verticesCount);
  for (size_t i = 0; i < verticesCount; ++i)
  {
    const size_t idx = i * 2;
    vertex[0] = pointsTmp[idx];
    vertex[1] = pointsTmp[idx + 1];
    vertex[2] = 0.0;
    vertex[3] = texcoordsTmp[idx];
    vertex[4] = texcoordsTmp[idx + 1];
    vertices.push_back(vertex);
  }

  const float minX{(vertices[0][0] + vertices[0][1]) / 2.0f};

  vec2f averageXY{0.0, 0.0};
  switch(alignment.horizontal)
  {
    case Text::AlignmentHorizontal::left:
      break;
    case Text::AlignmentHorizontal::center:
    {
      for (auto& vertexAligned : vertices)
      {
        averageXY[0] += vertexAligned[0];
      }
      averageXY[0] /= static_cast<float>(verticesCount);

      for (auto& vertexAligned : vertices)
      {
        vertexAligned[0] += minX - averageXY[0];
      }
    }
      break;
    case Text::AlignmentHorizontal::right:
    {
      for (auto& vertexAligned : vertices)
      {
        averageXY[0] += vertexAligned[0];
      }
      averageXY[0] /= static_cast<float>(verticesCount);

      for (auto& vertexAligned : vertices)
      {
        vertexAligned[0] += 2.0f * (minX - averageXY[0]);
      }
    }
      break;
  }

  buffer.mElements = vertices.size();

  glBindBuffer(GL_ARRAY_BUFFER, buffer.mName);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * vertex.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
}

} // namespace rwc