#version 300 es

precision lowp float;

in vec2 vTexCoords;

out vec4 fColor;

uniform sampler2D uSamplerDiffuse;
uniform vec4 uColor;

void main()
{
    vec4 color = texture(uSamplerDiffuse, vTexCoords);
    fColor.rgb = color.rgb * uColor.rgb;
    fColor.a = color.a;
}
