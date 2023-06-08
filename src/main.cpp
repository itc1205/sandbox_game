#include "core/engine.hpp"
#include "core/input.hpp"
#include "core/mouse.hpp"
#include "core/window.hpp"
#include "draw/shader.hpp"
#include "draw/texture.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/geometric.hpp"

#include <GL/gl.h>
#include <GL/glext.h>
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <iostream>

#include <logger/logger.hpp>

const float cameraSpeed = 0.01f;

void change_to_wireframe_rendering_mode() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void change_to_fill_rendering_mode() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main() {
  Engine::init();
  Engine::Window::create();
  Engine::Input::create_mapping(Engine::Input::Key{GLFW_KEY_SPACE, GLFW_PRESS},
                                change_to_wireframe_rendering_mode);
  Engine::Input::create_mapping(
      Engine::Input::Key{GLFW_KEY_SPACE, GLFW_RELEASE},
      change_to_fill_rendering_mode);

  glfwSetInputMode(Engine::window, GLFW_STICKY_KEYS, GLFW_TRUE);

  auto shader = Engine::Draw::Shader("../assets/shaders/vert.vs",
                                     "../assets/shaders/frag.fs");
  glEnable(GL_DEPTH_TEST);

  while (!Engine::shouldClose()) {
    Engine::tick();
  }
  Engine::terminate();
}
