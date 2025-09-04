#include "object.h"

object_t object_init(char* mesh_path) {
  object_t result;

  result.mesh = mesh_load(mesh_path, &result.material);
  mesh_setup(&result.mesh);

  result.transform = (transform_t){
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {1.0f, 1.0f, 1.0f},
  };

  return result;
}
