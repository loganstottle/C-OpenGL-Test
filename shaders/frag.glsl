#version 460 core

in vec3 pos_eye;
in vec3 normal_local;

in vec2 tex_coord;

out vec4 FragColor;

uniform mat4 u_view;
uniform mat4 u_modelview;
uniform sampler2D u_tex0;
uniform vec4 u_color;

vec3 light_pos = vec3(-2.5, 2.5, 2.5);

void main() {
  light_pos = (u_view * vec4(light_pos, 1.0)).xyz;
  vec3 light_dir = normalize(pos_eye - light_pos);
  float strength = (dot(-light_dir, normal_local) + 1.0) / 2.0;

  FragColor = strength * u_color; //texture(u_tex0, tex_coord);
}
