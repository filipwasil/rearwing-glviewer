#version 300 es

precision lowp float;

in vec3 vNormals;
in vec2 vTexCoords;

out vec4 fColor;

uniform sampler2D uSamplerDiffuse;

void main()
{
    fColor = texture(uSamplerDiffuse, vTexCoords);
}
