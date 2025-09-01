#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "shader.h"
#include "texture.h"
#include "window.h"
#include "transform.h"
#include "camera.h"
#include "mesh.h"

int main() {
  float window_width = 1200;
  float window_height = 800;

  float fov = 60;

  float near_plane = 0.1;
  float far_plane = 100;

  window_t window = window_init(window_width, window_height, false, "Test");

  mesh_t suzanne = mesh_load("./assets/suzanne/scene.gltf");
  mesh_setup(&suzanne);

  shader_t shader = shader_load("shaders/vert.glsl", "shaders/frag.glsl");
  shader_set_uniform_1i(shader, "u_tex0", 0); // 0 corresponds to GL_TEXTURE0

  transform_t square_transform = {
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {1.0f, 1.0f, 1.0f},
  };

  camera_t camera = {0};

  camera.speed = 5;
  camera.sensitivity = 1;

  camera.position[2] += 5;

  mat4 model, view, projection, model_view;

  transform_to_model_matrix(square_transform, model);

  camera_to_matrix(camera, view);
  shader_set_uniform_matrix_4fv(shader, "u_view", view);

  glm_mat4_mul(view, model, model_view);
  shader_set_uniform_matrix_4fv(shader, "u_modelview", model_view);

  glm_perspective(glm_rad(fov), window_width / window_height, near_plane, far_plane, projection);
  shader_set_uniform_matrix_4fv(shader, "u_projection", projection);
 
  texture_t cat_texture = texture_load("cat.jpg", GL_TEXTURE0);

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0, 0, 0, 1.0);

  while (window_alive(window)) {
    window_update(&window); // poll events & update dt
    if (window_iskeydown(window, GLFW_KEY_ESCAPE)) break;
    camera_inputs(&camera, window);

    if (camera.dirty) {
      camera_to_matrix(camera, view);
      shader_set_uniform_matrix_4fv(shader, "u_view", view);
    }

    square_transform.position[1] = sin(2 * glfwGetTime());

    square_transform.rotation[1] += 0.15;
    square_transform.rotation[2] += 0.15;

    transform_to_model_matrix(square_transform, model);

    glm_mat4_mul(view, model, model_view);
    shader_set_uniform_matrix_4fv(shader, "u_modelview", model_view);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mesh_draw(&suzanne, camera);

    window_render(window); // swap buffers
  }

  glDeleteProgram(shader.id);
  glDeleteTextures(1, &cat_texture.id);

  window_cleanup(window);

  return 0;
}
