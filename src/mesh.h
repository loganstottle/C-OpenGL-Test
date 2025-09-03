#ifndef MESH_H
#define MESH_H

#include "vao.h"
#include "vertex.h"
#include "buffer.h"
#include "texture.h"
#include "camera.h"

typedef struct {
  vertex_t* vertices;
  unsigned int* indices;
  texture_t* textures;

  int num_vertices, num_indices, num_textures;

  vao_t vao;
  buffer_t vbo, ibo;
} mesh_t;

mesh_t mesh_load(char* path);
void mesh_setup(mesh_t* mesh);
void mesh_draw(mesh_t* mesh);

#endif
