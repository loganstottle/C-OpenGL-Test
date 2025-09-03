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

#endif
