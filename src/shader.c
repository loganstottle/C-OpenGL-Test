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
  unsigned int vert_shader = shader_compile("shaders/vert.glsl", GL_VERTEX_SHADER);
  unsigned int frag_shader = shader_compile("shaders/frag.glsl", GL_FRAGMENT_SHADER);

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

void shader_unbind(shader_t shader) {
  glUseProgram(0);
}

bool check_uniform_location(int uniform_location, const char* name) {
  bool ok = uniform_location != -1;

  if (!ok)
    printf("shader uniform \"%s\" does not exist\n", name);

  return ok;
}

void shader_set_uniform_1i(shader_t shader, const char* name, int v0) {
  int uniform_location = glGetUniformLocation(shader.id, name);

  if (check_uniform_location(uniform_location, name))
    glUniform1i(uniform_location, v0);
}

void shader_set_uniform_matrix_4fv(shader_t shader, const char* name, mat4 matrix) {
  int uniform_location = glGetUniformLocation(shader.id, name);

  if (check_uniform_location(uniform_location, name))
    glUniformMatrix4fv(uniform_location, 1, GL_FALSE, (GLfloat*)matrix);
}

void shader_set_uniform_matrix_3fv(shader_t shader, const char* name, mat3 matrix) {
  int uniform_location = glGetUniformLocation(shader.id, name);

  if (check_uniform_location(uniform_location, name))
    glUniformMatrix3fv(uniform_location, 1, GL_FALSE, (GLfloat*)matrix);
}

void shader_set_uniform_3fv(shader_t shader, const char* name, vec3 vector) {
  int uniform_location = glGetUniformLocation(shader.id, name);

  if (check_uniform_location(uniform_location, name))
    glUniform3fv(uniform_location, 1, (GLfloat*)vector);
}
