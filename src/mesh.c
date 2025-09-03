#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"

mesh_t mesh_load(char* path) {
  mesh_t result;

  const struct aiScene* scene = aiImportFile(path,
    aiProcess_Triangulate |
    aiProcess_JoinIdenticalVertices |
    aiProcess_GenSmoothNormals |
    aiProcess_SortByPType
  );

  if (!scene) {
    const char* error = aiGetErrorString();
    printf("failed to load model %s\n: %s\n", path, error);
    exit(EXIT_FAILURE);
  }

  if (scene->mNumMeshes != 1)
    printf("TODO: MORE THAN ONE MESH PER SCENE");

  struct aiMesh* mesh = scene->mMeshes[0];

  result.num_vertices = mesh->mNumVertices;
  result.vertices = malloc(result.num_vertices * sizeof(vertex_t));

  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    struct aiVector3D normal = mesh->mNormals[i];
    struct aiVector3D position = mesh->mVertices[i];
    struct aiVector3D tex_coords = mesh->mTextureCoords[0][i]; // TODO: FIX

    result.vertices[i] = (vertex_t){{position.x, position.y, position.z}, {normal.x, normal.y, normal.z}, {tex_coords.x, tex_coords.y}};
  }

  result.num_indices = 3 * mesh->mNumFaces;
  result.indices = malloc(result.num_indices * sizeof(unsigned int));

  for (unsigned int i = 0; i < mesh->mNumFaces; i++)
  for (unsigned int j = 0; j < 3; j++)
    result.indices[i * 3 + j] = mesh->mFaces[i].mIndices[j];

  return result;
}

void mesh_setup(mesh_t* mesh) {
  mesh->vao = vao_create();

  mesh->vbo = buffer_create(GL_ARRAY_BUFFER);
  buffer_set(mesh->vbo, (void*)mesh->vertices, mesh->num_vertices * sizeof(vertex_t), GL_STATIC_DRAW);

  vao_stride(&mesh->vao, sizeof(vertex_t));

  vao_attrib(&mesh->vao, 3, GL_FLOAT, GL_FALSE, offsetof(vertex_t, position));
  vao_attrib(&mesh->vao, 3, GL_FLOAT, GL_FALSE, offsetof(vertex_t, normal));
  vao_attrib(&mesh->vao, 2, GL_FLOAT, GL_FALSE, offsetof(vertex_t, tex_coord));

  mesh->ibo = buffer_create(GL_ELEMENT_ARRAY_BUFFER);
  buffer_set(mesh->ibo, (void*)mesh->indices, mesh->num_indices * sizeof(unsigned int), GL_STATIC_DRAW);
}

void mesh_draw(mesh_t* mesh) {
  vao_bind(mesh->vao);

  buffer_bind(mesh->vbo);
  buffer_bind(mesh->ibo);

  glDrawElements(GL_TRIANGLES, mesh->num_indices, GL_UNSIGNED_INT, NULL);
}
