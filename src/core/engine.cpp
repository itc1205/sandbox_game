#include <core/engine.hpp>

namespace Engine {

GLFWwindow *window = nullptr;

uint WIDTH = 640;
uint HEIGHT = 480;

void init() {

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void setup_callbacks() {
  glfwSetFramebufferSizeCallback(window, Callbacks::framebuffer_size_callback);
  glfwSetKeyCallback(window, Callbacks::key_callback);
}

int exit_with_error(int error) {
  Logger::error("Error just happened, exiting...");
  exit(error);
}

void tick() {
  glfwSwapBuffers(window);
  glfwPollEvents();
}

bool shouldClose() { return glfwWindowShouldClose(window); }

void terminate() { glfwTerminate(); }

} // namespace Engine