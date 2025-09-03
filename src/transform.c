#include "transform.h"

void transform_to_model_matrix(transform_t transform, mat4 out) {
  mat4 scale, rotate, translate, temp, rotx, roty, rotz;

  glm_scale_make(scale, transform.scale);
  glm_translate_make(translate, transform.position);

  glm_rotate_make(rotx, glm_rad(transform.rotation[0]), (vec3){1.0f, 0.0f, 0.0f});
  glm_rotate_make(roty, glm_rad(transform.rotation[1]), (vec3){0.0f, 1.0f, 0.0f});
  glm_rotate_make(rotz, glm_rad(transform.rotation[2]), (vec3){0.0f, 0.0f, 1.0f});

  glm_mat4_mul(roty, rotx, temp);
  glm_mat4_mul(rotz, temp, rotate);

  glm_mat4_mul(rotate, scale, temp);
  glm_mat4_mul(translate, temp, out);
}

void transform_set_position(transform_t* transform, float x, float y, float z) {
  transform->position[0] = x;
  transform->position[1] = y;
  transform->position[2] = z;
}

void transform_set_rotation(transform_t* transform, float x, float y, float z) {
  transform->rotation[0] = x;
  transform->rotation[1] = y;
  transform->rotation[2] = z;
}

void transform_set_scale(transform_t* transform, float x, float y, float z) {
  transform->scale[0] = x;
  transform->scale[1] = y;
  transform->scale[2] = z;
}
