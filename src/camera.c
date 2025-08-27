#include "camera.h"
#include "window.h"

void camera_update_orientation(camera_t* camera) {
  camera->orientation[0] = cosf(glm_rad(camera->pitch)) * sinf(glm_rad(camera->yaw));
  camera->orientation[1] = sinf(glm_rad(camera->pitch));
  camera->orientation[2] = -cosf(glm_rad(camera->pitch)) * cosf(glm_rad(camera->yaw));

  glm_vec3_cross(camera->orientation, (vec3){0.0f, 1.0f, 0.0f}, camera->right);

  glm_normalize(camera->orientation);
  glm_normalize(camera->right);
}

void camera_to_matrix(camera_t camera, mat4 out_matrix) {
  vec3 center;
  glm_vec3_add(camera.position, camera.orientation, center);

  glm_lookat(camera.position, center, (vec3){0.0f, 1.0f, 0.0f}, out_matrix);
}

void camera_inputs(camera_t* camera, window_t window) {
  // todo - fix
  if (window.frame == 1) {
    camera_update_orientation(camera);
    camera->dirty = true;
  }

  if (window.delta_x != 0 || window.delta_y != 0) {
    camera->yaw += window.delta_x * camera->sensitivity * 0.1;
    camera->pitch -= window.delta_y * camera->sensitivity * 0.1;

    camera->pitch = fminf(fmaxf(camera->pitch, -89.0f), 89.0f);

    camera_update_orientation(camera);
    camera->dirty = true;
  }

  if (window_iskeydown(window, GLFW_KEY_W)) {
    vec3 flat_orientation, delta_pos;

    glm_vec3_cross((vec3){0.0f, 1.0f, 0.0f}, camera->right, flat_orientation);
    glm_vec3_scale(flat_orientation, camera->speed * window.delta_time, delta_pos);
    glm_vec3_add(camera->position, delta_pos, camera->position);

    camera->dirty = true;
  }

  if (window_iskeydown(window, GLFW_KEY_S)) {
    vec3 flat_orientation, delta_pos;

    glm_vec3_cross((vec3){0.0f, 1.0f, 0.0f}, camera->right, flat_orientation);
    glm_vec3_scale(flat_orientation, camera->speed * window.delta_time, delta_pos);
    glm_vec3_sub(camera->position, delta_pos, camera->position);

    camera->dirty = true;
  }

  if (window_iskeydown(window, GLFW_KEY_D)) {
    vec3 flat_orientation, delta_pos;

    glm_vec3_scale(camera->right, camera->speed * window.delta_time, delta_pos);
    glm_vec3_add(camera->position, delta_pos, camera->position);

    camera->dirty = true;
  }

  if (window_iskeydown(window, GLFW_KEY_A)) {
    vec3 flat_orientation, delta_pos;

    glm_vec3_scale(camera->right, camera->speed * window.delta_time, delta_pos);
    glm_vec3_sub(camera->position, delta_pos, camera->position);

    camera->dirty = true;
  }

  if (window_iskeydown(window, GLFW_KEY_SPACE)) {
    glm_vec3_add(camera->position, (vec3){0.0f, camera->speed * window.delta_time, 0.0f}, camera->position);
    camera->dirty = true;
  }

  if (window_iskeydown(window, GLFW_KEY_LEFT_SHIFT)) {
    glm_vec3_sub(camera->position, (vec3){0.0f, camera->speed * window.delta_time, 0.0f}, camera->position);
    camera->dirty = true;
  }
}
