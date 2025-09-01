#include <glad/glad.h>

#include "vao.h"

vao_t vao_create() {
  vao_t result = {0};

  glGenVertexArrays(1, &result.id);
  vao_bind(result);

  return result;
}

void vao_stride(vao_t* vao, size_t stride) {
  vao->stride = stride;
}

void vao_attrib(vao_t* vao, int count, unsigned int type, unsigned char normalized, size_t offset) {
  glVertexAttribPointer(vao->attrib_count, count, type, normalized, vao->stride, (void*)offset);
  glEnableVertexAttribArray(vao->attrib_count++);
}

void vao_bind(vao_t vao) {
  glBindVertexArray(vao.id);
}

void vao_unbind() {
  glBindVertexArray(0);
}
