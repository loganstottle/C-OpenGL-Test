#version 460 core

in vec3 pos;
in vec3 normal;
in vec2 tex_coord;

out vec4 FragColor;

uniform sampler2D u_tex0;

void main() {
  FragColor = texture(u_tex0, tex_coord);
}
