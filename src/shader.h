#ifndef SHADER_H
#define SHADER_H

#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

typedef struct {
  unsigned int id;
} shader_t;

shader_t shader_load(const char* vert, const char* frag);
void shader_bind(shader_t shader);
void shader_unbind();
void shader_set_uniform_1i(shader_t shader, const char* name, int v0);
void shader_set_uniform_matrix_3fv(shader_t shader, const char* name, mat3 matrix);
void shader_set_uniform_matrix_4fv(shader_t shader, const char* name, mat4 matrix);
void shader_set_uniform_3fv(shader_t shader, const char* name, vec3 vector);

#endif
