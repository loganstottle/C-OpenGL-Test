#ifndef VAO_H
#define VAO_H

#include <stdlib.h>

typedef struct {
  unsigned int id, attrib_count;
  size_t stride;
} vao_t;

vao_t vao_create();
void vao_stride(vao_t* vao, size_t stride);
void vao_attrib(vao_t* vao, int count, unsigned int type, unsigned char normalized, size_t offset);
void vao_bind(vao_t vao);
void vao_unbind();

#endif
