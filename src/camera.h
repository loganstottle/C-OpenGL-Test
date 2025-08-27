#ifndef CAMERA_H
#define CAMERA_H

#include "transform.h"
#include "window.h"

typedef struct {
  vec3 position, orientation, right;
  float pitch, yaw;
  float sensitivity;
  float speed;
  bool dirty;
} camera_t;

void camera_to_matrix(camera_t camera, mat4 out_matrix);
void camera_inputs(camera_t* camera, window_t window);

#endif
