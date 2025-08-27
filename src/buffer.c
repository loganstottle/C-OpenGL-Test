#include "buffer.h"
#include <glad/glad.h>
#include <stdio.h>

buffer_t buffer_create(unsigned int target) {
  buffer_t result = {0, target};

  glGenBuffers(1, &result.id);
  buffer_bind(result);

  return result;
}

void buffer_set(buffer_t buffer, void* vertices, size_t size, GLenum usage) {
  glBufferData(buffer.target, size, vertices, usage);
}

void buffer_bind(buffer_t buffer) {
  glBindBuffer(buffer.target, buffer.id);
}

void buffer_unbind(buffer_t buffer) {
  glBindBuffer(buffer.target, 0);
}
