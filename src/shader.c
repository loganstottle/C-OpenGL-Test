#include <glad/glad.h>
#include <cglm/cglm.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "shader.h"

#define MAX_SHADER_ERROR_LENGTH 512

GLuint shader_compile(const char* path, GLenum type) {
  FILE* f = fopen(path, "r");
  if (!f) {
    printf("failed to open file \"%s\"\n", path);
    exit(1);
  }

  fseek(f, 0, SEEK_END);

  int file_size = ftell(f);
  rewind(f);

  char* bytes = malloc(file_size + 1);
  fread((void*)bytes, 1, file_size, f);
  bytes[file_size] = '\0';
  fclose(f);

  const GLchar* const contents = bytes;

  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &contents, NULL);
  glCompileShader(shader);

  free((void*)bytes);

  int success;
  char info[MAX_SHADER_ERROR_LENGTH];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, MAX_SHADER_ERROR_LENGTH, NULL, info);
    printf("Shader compilation failed (%s): \n%s\n", path, info);
    exit(EXIT_FAILURE);
  }

  return shader;
}

shader_t shader_load(const char* vert, const char* frag) {
  unsigned int vert_shader = shader_compile(vert, GL_VERTEX_SHADER);
  unsigned int frag_shader = shader_compile(frag, GL_FRAGMENT_SHADER);

  unsigned int shader_program = glCreateProgram();
  glAttachShader(shader_program, vert_shader);
  glAttachShader(shader_program, frag_shader);
  glLinkProgram(shader_program);

  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);

  glUseProgram(shader_program);

  return (shader_t){shader_program};
}

void shader_bind(shader_t shader) {
  glUseProgram(shader.id);
}

void shader_unbind() {
  glUseProgram(0);
}
