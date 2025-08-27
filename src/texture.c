#include <glad/glad.h>
#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

texture_t texture_load(const char* file_name, GLenum texture_unit) {
  texture_t result;

  stbi_set_flip_vertically_on_load(1);

  unsigned char* image_data = stbi_load(file_name, &result.width, &result.height, &result.channels, 0);

  glGenTextures(1, &result.id);
  texture_bind(result, texture_unit);

  // todo: custom texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  int color_channel_type;

  switch (result.channels) {
    case 3:
      color_channel_type = GL_RGB; break;
    case 4:
      color_channel_type = GL_RGBA; break;
    default:
      printf("fatal: failed to load texture %s: unknown amount of color channels: %d\n", file_name, result.channels);
      exit(1);
  };

  glTexImage2D(GL_TEXTURE_2D, 0, color_channel_type, result.width, result.height, 0, color_channel_type, GL_UNSIGNED_BYTE, image_data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(image_data);

  return result;
}

void texture_bind(texture_t texture, GLenum texture_unit) {
  glActiveTexture(texture_unit);
  glBindTexture(GL_TEXTURE_2D, texture.id);
}

void texture_unbind(texture_t texture) {
  glBindTexture(GL_TEXTURE_2D, 0);
}
