#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "shader.h"
#include "window.h"
#include "transform.h"
#include "camera.h"
#include "mesh.h"
#include "material.h"
#include "object.h"

void render_object(object_t object, camera_t camera) {
  mat4 model, view, model_view;
 
  if (camera.dirty) {
    camera_to_matrix(camera, view);
    camera.dirty = false;
  }

  for (int i = 0; i < object.material.num_textures; i++)
    texture_bind(object.material.textures[i]);
 
  transform_to_model_matrix(object.transform, model);

  material_set_uniform_mat4(&object.material, "u_view", view);

  glm_mat4_mul(view, model, model_view);
  material_set_uniform_mat4(&object.material, "u_modelview", model_view);

  material_set_uniform_mat4(&object.material, "u_projection", camera.projection);

  material_apply_uniforms(object.material);
  mesh_draw(&object.mesh);

  texture_unbind();
}

int main() {
  float window_width = 1200;
  float window_height = 800;

  float fov = 60;

  float near_plane = 0.1;
  float far_plane = 100;

  window_t window = window_init(window_width, window_height, false, "Test");

  camera_t camera = camera_init(1, 5, fov, window_width / window_height, near_plane, far_plane);
  camera.position[2] += 5;

  shader_t shader = shader_load("shaders/vert.glsl", "shaders/frag.glsl");

  object_t suzanne = object_init("./assets/suzanne/scene.gltf");
  transform_set_scale(&suzanne.transform, 0.5, 0.5, 0.5);
  transform_set_position(&suzanne.transform, -1, 0, 0);

  material_set_shader(&suzanne.material, shader);
  material_set_color(&suzanne.material, 1, 0, 0, 1);

  material_set_uniform_vec4(&suzanne.material, "u_color", suzanne.material.color);
  material_set_uniform_int(&suzanne.material, "u_textured", 0);

  object_t cat = object_init("./assets/Kitten/Mesh_Kitten.obj");
  transform_set_scale(&cat.transform, 0.05, 0.05, 0.05);
  transform_set_position(&cat.transform, 1, 0, 0);

  material_set_shader(&cat.material, shader);

  material_set_uniform_int(&cat.material, "u_tex0", 0);
  material_set_uniform_int(&cat.material, "u_textured", 1);

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0, 0, 0, 1.0);

  while (window_alive(window)) {
    window_update(&window); // poll events & update dt
    if (window_iskeydown(window, GLFW_KEY_ESCAPE)) break;
    camera_inputs(&camera, window);

    suzanne.transform.position[1] = sin(4 * glfwGetTime());

    suzanne.transform.rotation[1] += 0.25;
    suzanne.transform.rotation[2] += 0.15;

    cat.transform.position[1] = -sin(3 * glfwGetTime());

    cat.transform.rotation[1] -= 0.15;
    cat.transform.rotation[2] -= 0.25;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    render_object(suzanne, camera);
    render_object(cat, camera);

    window_render(window); // swap buffers
  }

  window_cleanup(window);

  return 0;
}
