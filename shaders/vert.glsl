#version 460 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec4 a_color;
layout (location = 3) in vec2 a_tex;

uniform mat4 u_modelview;
uniform mat4 u_projection;

out mat4 model_view;
out vec2 tex_coord;

// view space
out vec3 pos_eye;
out vec3 normal_local;

mat3 normal_matrix = transpose(inverse(mat3(u_modelview)));

void main() {
  gl_Position = u_projection * u_modelview * vec4(a_pos, 1.0);
  pos_eye = (u_modelview * vec4(a_pos, 1.0)).xyz;
  normal_local = normalize(normal_matrix * a_normal);
  tex_coord = a_tex;
}
