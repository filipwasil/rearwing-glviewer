#version 300 es

precision lowp float;

in vec2 vTexCoords;

out vec4 fColor;

void main( void )
{
    fColor = vec4(0.1, 1.0, 0.2, 1.0);
}