#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "shader.h"
#include "texture.h"
#include "window.h"
#include "buffer.h"
#include "vao.h"
#include "transform.h"
#include "camera.h"
#include "vertex.h"
#include "cube.h"

int main() {
  float window_width = 1200;
  float window_height = 800;

  float fov = 60;

  float near_plane = 0.1;
  float far_plane = 100;

  window_t window = window_init(window_width, window_height, false, "Test");

  vao_t vao = vao_create();

  buffer_t vbo = buffer_create(GL_ARRAY_BUFFER);
  buffer_set(vbo, (void*)cube_vertices, sizeof(cube_vertices), GL_STATIC_DRAW);

  vao_stride(&vao, sizeof(vertex_t));

  vao_attrib(&vao, 3, GL_FLOAT, GL_FALSE, offsetof(vertex_t, position));
  vao_attrib(&vao, 3, GL_FLOAT, GL_FALSE, offsetof(vertex_t, normal));
  vao_attrib(&vao, 3, GL_FLOAT, GL_FALSE, offsetof(vertex_t, color));
  vao_attrib(&vao, 2, GL_FLOAT, GL_FALSE, offsetof(vertex_t, tex_coord));

  buffer_t ibo = buffer_create(GL_ELEMENT_ARRAY_BUFFER);
  buffer_set(ibo, (void*)cube_indices, sizeof(cube_indices), GL_STATIC_DRAW);

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
  mat3 normal;

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

    square_transform.rotation[1] += 0.1;
    square_transform.rotation[2] += 0.1;

    transform_to_model_matrix(square_transform, model);

    glm_mat4_mul(view, model, model_view);
    shader_set_uniform_matrix_4fv(shader, "u_modelview", model_view);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, sizeof(cube_indices) / sizeof(unsigned int), GL_UNSIGNED_INT, NULL);

    window_render(window); // swap buffers
  }

  glDeleteVertexArrays(1, &vao.id);
  glDeleteBuffers(1, &vbo.id);
  glDeleteBuffers(1, &ibo.id);
  glDeleteProgram(shader.id);
  glDeleteTextures(1, &cat_texture.id);

  window_cleanup(window);

  return 0;
}
