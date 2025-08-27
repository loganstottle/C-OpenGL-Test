#include "transform.h"

void transform_to_normal_matrix(transform_t transform, mat4 out_matrix) {
  glm_mat4_identity(out_matrix);
  glm_rotate(out_matrix, glm_rad(transform.rotation[0]), (vec3){1.0f, 0.0f, 0.0f});
  glm_rotate(out_matrix, glm_rad(transform.rotation[1]), (vec3){0.0f, 1.0f, 0.0f});
  glm_rotate(out_matrix, glm_rad(transform.rotation[2]), (vec3){0.0f, 0.0f, 1.0f});
  glm_mat4_inv(out_matrix, out_matrix);
}

void transform_to_model_matrix(transform_t transform, mat4 out_matrix) {
  glm_mat4_identity(out_matrix);
  glm_rotate(out_matrix, glm_rad(transform.rotation[0]), (vec3){1.0f, 0.0f, 0.0f});
  glm_rotate(out_matrix, glm_rad(transform.rotation[1]), (vec3){0.0f, 1.0f, 0.0f});
  glm_rotate(out_matrix, glm_rad(transform.rotation[2]), (vec3){0.0f, 0.0f, 1.0f});
  glm_translate(out_matrix, transform.position);
  glm_scale(out_matrix, transform.scale);
}
