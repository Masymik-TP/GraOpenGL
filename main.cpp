#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// ---------========= Własne pliki nagłówkowe =========----------
#include "./src/env.h"
// ---------===========================================----------

int main() {
  Env env;
  env.widowWidth = 800;
  env.windowHeight = 600;

  if (!glfwInit()) return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(env.widowWidth, env.windowHeight, "Gra", NULL, NULL);

  if (!window) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return -1;
  glViewport(0, 0, env.widowWidth, env.windowHeight);

  // -----========= GŁÓWNA PĘTLA GRY =========-----
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  // -----====================================-----

  glfwTerminate();
  return 0;
}