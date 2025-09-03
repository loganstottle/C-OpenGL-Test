#ifndef OBJECT_H
#define OBJECT_H

#include "transform.h"
#include "mesh.h"
#include "material.h"

typedef struct {
  transform_t transform;
  mesh_t mesh;
  material_t material;
} object_t;

object_t object_init(char* mesh_path);

#endif
