#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

typedef struct {
  int width, height, channels;
  unsigned int id;
} texture_t;

texture_t texture_load(const char* file_name, GLenum texture_unit);
void texture_bind(texture_t texture, GLenum texture_unit);
void texture_unbind(texture_t texture);

#endif
