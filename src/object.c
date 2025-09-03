#include "object.h"

object_t object_init(char* mesh_path) {
  object_t result;

  result.mesh = mesh_load(mesh_path);
  mesh_setup(&result.mesh);

  result.material = (material_t){{1.0, 1.0, 1.0, 1.0}, {0}, {{0}}, 0};

  result.transform = (transform_t){
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {1.0f, 1.0f, 1.0f},
  };

  return result;
}
