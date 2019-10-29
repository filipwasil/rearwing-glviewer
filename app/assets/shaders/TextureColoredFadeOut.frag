#version 300 es

precision lowp float;

in vec2 vTexCoords;
in float vDepth;

out vec4 fColor;

uniform sampler2D uSamplerDiffuse;
uniform vec4 uColor;

void main()
{
    vec4 color = texture(uSamplerDiffuse, vTexCoords);
    fColor.rgb = color.rgb * uColor.rgb;
    fColor.rgb *= 1.5 * (1.0 - 0.6 * vDepth);
    fColor.a = color.a;
}
