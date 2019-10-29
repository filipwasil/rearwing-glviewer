#version 300 es

precision lowp float;

in vec3 vNormals;
in vec2 vTexCoords;

out vec4 fColor;

uniform float uTime;

void main() {
  float colorModifier = mix(0.0, 1.0, 0.5 + abs(0.5 - (0.15 * uTime - float(int(0.15 * uTime)))));
  fColor = vec4(vNormals * colorModifier, 1.0);
}
