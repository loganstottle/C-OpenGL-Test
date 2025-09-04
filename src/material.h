#ifndef MATERIAL_H
#define MATERIAL_H

#include "shader.h"
#include "texture.h"

#define MAX_UNIFORMS 8
#define MAX_TEXTURES 8

typedef struct {
  const char* name;
  enum {
    INT,
    VEC3,
    VEC4,
    MAT3,
    MAT4
  } type;
  union {
    int INT;
    vec3 VEC3;
    vec4 VEC4;
    mat3 MAT3;
    mat4 MAT4;
  } data;
} uniform_t;

typedef struct {
  vec4 color;
  shader_t shader;
  uniform_t uniforms[MAX_UNIFORMS];
  int num_uniforms;
  texture_t textures[MAX_TEXTURES];
  int num_textures;
} material_t;

void material_set_color(material_t* material, float r, float g, float b, float a);
void material_set_shader(material_t* material, shader_t shader);
void material_set_uniform_int(material_t* material, const char* name, int n);
void material_set_uniform_vec3(material_t* material, const char* name, vec3 v);
void material_set_uniform_vec4(material_t* material, const char* name, vec4 v);
void material_set_uniform_mat3(material_t* material, const char* name, mat3 m);
void material_set_uniform_mat4(material_t* material, const char* name, mat4 m);
void material_apply_uniforms(material_t material);
void material_add_texture(material_t* material, char* texture_path);

#endif
