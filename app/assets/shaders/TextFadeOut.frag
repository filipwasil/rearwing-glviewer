#version 300 es

precision lowp float;

in vec2 vTexCoords;
in float vDepth;

out vec4 fColor;

uniform sampler2D uTextureUnit;
uniform vec4 uColor;

void main ()
{
    float pixelSize = 0.001;
    vec4 color = vec4(0.0);
    for (float i=-1.0;i<=1.0;i++)
        for (float j=-1.0;j<=1.0;j++)
            color += texture(uTextureUnit, vTexCoords + pixelSize * vec2(i, j));
    fColor = color * uColor * 0.11;
    fColor.rgb *= 1.5 * (1.0 - 0.6 * vDepth);
    if (length(fColor.rgb) < 0.001)
        discard;
}
