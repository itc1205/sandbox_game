#include "core/engine.hpp"
#include <core/window.hpp>
#include <logger/logger.hpp>

namespace Engine::Window {
GLFWwindow *create() {

  if (Engine::window == nullptr) {
    Logger::info("Creating new window!");
    Engine::window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);
    glfwMakeContextCurrent(window);
  } else {
    Logger::warn(
        "Window is already exists!, hovewer i'll return a same one "
        "and make context of this one current with ressetupping callbacks!");
  }

  if (Engine::window == nullptr) {
    Logger::error(
        "Failed to create window! Maybe you should call init firstly...");
    exit_with_error(-1);
  }
  // Post-init calls
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    Logger::error("Failed to initialize GLAD");
    exit_with_error(-1);
  }
  glfwMakeContextCurrent(window);
  glViewport(0, 0, WIDTH, HEIGHT);
  setup_callbacks();
  return window;
}

} // namespace Engine::Window

namespace Engine::Callbacks {
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
} // namespace Engine::Callbacks