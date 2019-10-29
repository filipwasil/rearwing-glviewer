#version 300 es

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormals;
layout (location = 2) in vec2 aTexCoords;

out vec3 vNormals;
out vec2 vTexCoords;

uniform mat4 uMVP;

void main() {
  vTexCoords = aTexCoords;
  vNormals = aNormals;
  gl_Position = uMVP * vec4(aPosition, 1.0);
}
