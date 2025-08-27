#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

typedef struct {
  int frame;
  int width, height;
  GLFWwindow* raw_window;
  double last_frame, delta_time;
  double mouse_x, mouse_y;
  double delta_x, delta_y;
} window_t;

window_t window_init(int width, int height, bool vsync, const char* title);
bool window_alive(window_t window);
bool window_iskeydown(window_t window, int key);
void window_update(window_t* window);
void window_render(window_t window);
void window_cleanup(window_t window);

#endif
