#version 460 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec4 a_color;
layout (location = 3) in vec2 a_tex;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec2 tex_coord;
out vec3 normal;

void main() {
  gl_Position = u_projection * u_view * u_model * vec4(a_pos, 1.0);

  normal = transpose(inverse(mat3(u_view * u_model))) * a_normal;
  tex_coord = a_tex;
}
