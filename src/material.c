#include <string.h>
#include <glad/glad.h>

#include "material.h"

void material_set_color(material_t* material, float r, float g, float b, float a) {
  material->color[0] = r;
  material->color[1] = g;
  material->color[2] = b;
  material->color[3] = a;
}

void material_set_shader(material_t* material, shader_t shader) {
  material->shader = shader;
}

void material_set_uniform(material_t* material, uniform_t uniform) {
  if (material->num_uniforms == MAX_UNIFORMS)
    printf("too many uniforms!\n");

  for (int i = 0; i < material->num_uniforms; i++)
    if (strcmp(material->uniforms[i].name, uniform.name) == 0) {
      material->uniforms[i].data = uniform.data;
      return;
    }

  material->uniforms[material->num_uniforms++] = uniform;
}

void material_set_uniform_int(material_t* material, const char* name, int n) {
  uniform_t u = {name, INT, {0}};
  u.data.INT = n;

  material_set_uniform(material, u);
}

void material_set_uniform_vec3(material_t* material, const char* name, vec3 v) {
  uniform_t u = {name, VEC3, {0}};
  memcpy(u.data.VEC3, v, sizeof(vec3));

  material_set_uniform(material, u);
}

void material_set_uniform_vec4(material_t* material, const char* name, vec4 v) {
  uniform_t u = {name, VEC4, {0}};
  memcpy(u.data.VEC4, v, sizeof(vec4));

  material_set_uniform(material, u);
}

void material_set_uniform_mat3(material_t* material, const char* name, mat3 m) {
  uniform_t u = {name, MAT3, {0}};
  memcpy(u.data.MAT3, m, sizeof(mat3));

  material_set_uniform(material, u);
}

void material_set_uniform_mat4(material_t* material, const char* name, mat4 m) {
  uniform_t u = {name, MAT4, {0}};
  memcpy(u.data.MAT4, m, sizeof(mat4));

  material_set_uniform(material, u);
}

void material_apply_uniforms(material_t material) {
  for (int j = 0; j < material.num_textures; j++)
    texture_bind(material.textures[j]);

  for (int i = 0; i < material.num_uniforms; i++) {
    uniform_t uniform = material.uniforms[i];
    int uniform_location = glGetUniformLocation(material.shader.id, uniform.name);

    if (uniform_location == -1) {
      //printf("uniform \"%s\" does not exist\n", uniform.name);
      continue;
    }

    switch (uniform.type) {
      case INT:
        glUniform1i(uniform_location, uniform.data.INT); break;
      case VEC3:
        glUniform3fv(uniform_location, 1, (GLfloat*)uniform.data.VEC3); break;
      case VEC4:
        glUniform4fv(uniform_location, 1, (GLfloat*)uniform.data.VEC4); break;
      case MAT3:
        glUniformMatrix3fv(uniform_location, 1, GL_FALSE, (GLfloat*)uniform.data.MAT3); break;
      case MAT4:
        glUniformMatrix4fv(uniform_location, 1, GL_FALSE, (GLfloat*)uniform.data.MAT4); break;
    }
  }
}

void material_add_texture(material_t* material, char* texture_path) {
  if (material->num_textures == MAX_TEXTURES) {
    printf("too many textures on material");
    return;
  }

  material->textures[material->num_textures] = texture_load(texture_path, GL_TEXTURE0 + material->num_textures);
  material->num_textures++;
}
