#include "core/timer.hpp"
#include <core/engine.hpp>
#include <core/mouse.hpp>
#include <string>

namespace Engine {

GLFWwindow *window = nullptr;

Timer engine_timer = Timer();

uint WIDTH = 640;
uint HEIGHT = 480;

void init() {

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  engine_timer.start();
}

void setup_callbacks() {
  glfwSetFramebufferSizeCallback(window, Callbacks::framebuffer_size_callback);
  glfwSetKeyCallback(window, Callbacks::key_callback);
  glfwSetCursorPosCallback(window, Callbacks::mouseCallback);
}

int exit_with_error(int error) {
  Logger::error("Error just happened, exiting...");
  exit(error);
}

void tick() {
  std::cout << "Frame was rendered with: " << engine_timer.get_tick_time()
            << std::endl;
  std::cout << "Time engine is working: " << engine_timer.get_time()
            << std::endl;
  std::cout << "Fps is: " << engine_timer.get_fps() << std::endl;
  glfwSwapBuffers(window);
  glfwPollEvents();
}

bool shouldClose() { return glfwWindowShouldClose(window); }

void terminate() { glfwTerminate(); }

} // namespace Engine