#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <cglm/cglm.h>

typedef struct {
  vec3 position, rotation, scale;
} transform_t;

void transform_to_normal_matrix(transform_t transform, mat4 out_matrix);
void transform_to_model_matrix(transform_t transform, mat4 out_matrix);

void transform_set_position(transform_t* transform, float x, float y, float z);
void transform_set_rotation(transform_t* transform, float x, float y, float z);
void transform_set_scale(transform_t* transform, float x, float y, float z);

#endif
