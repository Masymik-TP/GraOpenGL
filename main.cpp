#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>
#include <windows.h>
#include <iostream>

// ---------========= Własne pliki nagłówkowe =========----------
#include "./src/env.h"
// ---------===========================================----------

int main() {
  // Ustawianie zmiennych środowiskowych
  Env env;
  env.windowWidth = 800;
  env.windowHeight = 600;
  env.desiredFPS = 144.0;
  // ---=============================---

  timeBeginPeriod(1);

  if (!glfwInit()) return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(env.windowWidth, env.windowHeight, "Gra", NULL, NULL);

  if (!window) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return -1;
  glViewport(0, 0, env.windowWidth, env.windowHeight);
  glfwSwapInterval(0);

  glClearColor((float)(135.0f / 255.0f), (float)(206.0f / 255.0f), (float)(235.0f / 255.0f), 1.0f);
  std::chrono::steady_clock::time_point next_frame = std::chrono::steady_clock::now();
  auto lastFrameTime = std::chrono::steady_clock::now();
  auto frameTime = env.getFrameTime();
  int frames = 0;
  // -----========= GŁÓWNA PĘTLA GRY =========-----
  while (!glfwWindowShouldClose(window)) {
    // Logika FPS
    auto frameStart = std::chrono::steady_clock::now();
    double deltaTime = (frameStart - lastFrameTime).count();
    lastFrameTime = frameStart;
    // ---====---

    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();

    // Frame limiter i liczenie FPS
    auto now = std::chrono::steady_clock::now();
    if (next_frame > now) {
      std::this_thread::sleep_until(next_frame);
    }
    next_frame += std::chrono::duration_cast<std::chrono::steady_clock::duration>(frameTime);
    frames++;
    static auto lastFpsTime = std::chrono::steady_clock::now();

    auto elapsed =
        std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - lastFpsTime)
            .count();

    if (elapsed >= 1.0) {
      std::cout << frames << std::endl;
      frames = 0;
      lastFpsTime = std::chrono::steady_clock::now();
    }
    // ---====---
  }
  // -----====================================-----

  timeEndPeriod(1);
  glfwTerminate();
  return 0;
}