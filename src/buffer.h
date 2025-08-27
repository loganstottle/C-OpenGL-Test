#ifndef BUFFER_H
#define BUFFER_H

#include <stdlib.h>
#include <glad/glad.h>

typedef struct {
  unsigned int id, target;
} buffer_t;

buffer_t buffer_create(GLenum target);
void buffer_set(buffer_t buffer, void* vertices, size_t size, GLenum usage);
void buffer_bind(buffer_t buffer);
void buffer_unbind(buffer_t buffer);

#endif
