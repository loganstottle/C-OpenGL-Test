#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "window.h"

window_t window_init(int width, int height, bool vsync, const char* title) {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!window) {
    const char* reason;
    glfwGetError(&reason);
    printf("fatal: GLFW failed to create window: %s\n", reason);
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(vsync);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  if(gladLoadGL() == 0) {
    printf("fatal: GLAD failed to load");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glViewport(0, 0, width, height);

  return (window_t){0, width, height, window, glfwGetTime(), 0};
}

bool window_alive(window_t window) {
  return !glfwWindowShouldClose(window.raw_window);
}

bool window_iskeydown(window_t window, int key) {
  return glfwGetKey(window.raw_window, key) == GLFW_PRESS;
}

void window_update(window_t* window) {
  window->delta_time = glfwGetTime() - window->last_frame;
  window->last_frame = glfwGetTime();

  glfwPollEvents();

  double old_mouse_x = window->mouse_x;
  double old_mouse_y = window->mouse_y;

  glfwGetCursorPos(window->raw_window, &window->mouse_x, &window->mouse_y);

  if (window->frame != 0) {
    window->delta_x = window->mouse_x - old_mouse_x;
    window->delta_y = window->mouse_y - old_mouse_y;
  }

  window->frame++;
}

void window_render(window_t window) {
  glfwSwapBuffers(window.raw_window);
}

void window_cleanup(window_t window) {
  glfwDestroyWindow(window.raw_window);
  glfwTerminate();
}
