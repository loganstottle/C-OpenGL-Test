#ifndef VERTEX_H
#define VERTEX_H

#include <cglm/cglm.h>

typedef struct {
  vec3 position, normal;
  vec4 color;
  vec2 tex_coord;
} vertex_t;

#endif
