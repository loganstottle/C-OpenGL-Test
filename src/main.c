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

int main() {
  float window_width = 1200;
  float window_height = 800;

  window_t window = window_init(window_width, window_height, false, "Test");

  vertex_t verts[] = {
    // front face
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},    // LDF
    {{-1.0f,  1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},    // LUF
    {{1.0f,  -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},    // RDF
    {{1.0f,   1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},    // RUF

    // back face
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},  // LDB
    {{-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},  // LUB
    {{1.0f,  -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},  // RDB
    {{1.0f,   1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},  // RUB
 
    // up face
    {{-1.0f, 1.0f,  1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},    // LUF
    {{-1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},    // LUB
    {{1.0f,  1.0f,  1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},    // RUF
    {{1.0f,  1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},    // RUB

    // down face
    {{-1.0f, -1.0f,  1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},  // LDF
    {{-1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},  // LDB
    {{1.0f,  -1.0f,  1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},  // RDF
    {{1.0f,  -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},  // RDB

    // left face
    {{-1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},  // LDB
    {{-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},  // LUB
    {{-1.0f, -1.0f,  1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},  // LDF
    {{-1.0f,  1.0f,  1.0f}, {0.0f, 1.0f,  0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},  // LUF

    // right face
    {{1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},   // RDB
    {{1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},   // RUB
    {{1.0f, -1.0f,  1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},   // RDF
    {{1.0f,  1.0f,  1.0f}, {0.0f, 1.0f,  0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},   // RUF
  };

  unsigned int indices[] = {
    // front face
    0, 3, 1,    // LDF, RUF, LUF
    0, 2, 3,    // LDF, RDF, RUF

    // back face
    6, 5, 7,    // RDB, LUB, RUB
    6, 4, 5,    // RDB, LDB, LUB

    // up face
    8, 11, 9,   // LUF, RUB, LUB
    8, 10, 11,  // LUF, RUF, RUB

    // down face
    13, 14, 12, // LDB, RDF, LDF
    13, 15, 14, // LDB, RDB, RDF

    // left face
    16, 19, 17, // LDB, LUF, LUB
    16, 18, 19, // LDB, LDF, LUF

    // right face
    22, 21, 23, // RDF, RUB, RUF
    22, 20, 21, // RDF, RDB, RUB
  };

  vao_t vao = vao_create();

  buffer_t vbo = buffer_create(GL_ARRAY_BUFFER);
  buffer_set(vbo, verts, sizeof(verts), GL_STATIC_DRAW);

  vao_stride(&vao, sizeof(vertex_t));

  vao_attrib(&vao, 3, GL_FLOAT, GL_FALSE, offsetof(vertex_t, position));
  vao_attrib(&vao, 3, GL_FLOAT, GL_FALSE, offsetof(vertex_t, normal));
  vao_attrib(&vao, 3, GL_FLOAT, GL_FALSE, offsetof(vertex_t, color));
  vao_attrib(&vao, 2, GL_FLOAT, GL_FALSE, offsetof(vertex_t, tex_coord));

  buffer_t ibo = buffer_create(GL_ELEMENT_ARRAY_BUFFER);
  buffer_set(ibo, indices, sizeof(indices), GL_STATIC_DRAW);

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
  shader_set_uniform_matrix_4fv(shader, "u_model", model);

  camera_to_matrix(camera, view);
  shader_set_uniform_matrix_4fv(shader, "u_view", view);

  glm_mat4_mul(view, model, model_view);
  glm_mat4_pick3t(model_view, normal);
  shader_set_uniform_matrix_3fv(shader, "u_normal", normal);

  glm_perspective(glm_rad(60.0f), window_width / window_height, 0.1f, 100.0f, projection);
  shader_set_uniform_matrix_4fv(shader, "u_projection", projection);
 
  texture_t cat_texture = texture_load("cat.jpg", GL_TEXTURE0);

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0, 0, 0, 1.0);

  while (window_alive(window)) {
    window_update(&window); // poll events & update dt

    if (window_iskeydown(window, GLFW_KEY_L))
      glfwSetInputMode(window.raw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (window_iskeydown(window, GLFW_KEY_ESCAPE))
      break;

    camera_inputs(&camera, window);

    if (camera.dirty) {
      camera_to_matrix(camera, view);
      shader_set_uniform_matrix_4fv(shader, "u_view", view);
    }

    square_transform.rotation[1] += 0.25;
    square_transform.rotation[2] += 0.25;

    if (window.frame % 1000 == 0)
      printf("FPS: %lf\n", 1 / window.delta_time);

    transform_to_model_matrix(square_transform, model);
    shader_set_uniform_matrix_4fv(shader, "u_model", model);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, NULL);

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
