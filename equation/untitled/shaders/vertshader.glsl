#version 410
// Vertex shader

layout (location = 0) in vec2 vertcoords_clip_vs;
layout (location = 1) in vec3 in_colour;

uniform float a = -1.0f;
uniform float b = 1.0f;

layout (location = 1) out vec3 out_colour;

void main() {
  float new_x = 2 * ( (vertcoords_clip_vs.x - a) / (b - a) ) - 1;
  vec2 coords = vec2(new_x, vertcoords_clip_vs.y);
  gl_Position = vec4(coords, 0.0, 1.0);
  out_colour = in_colour;
}
