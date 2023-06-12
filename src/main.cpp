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
#include <string>
#include <sys/types.h>

const float cameraSpeed = 0.01f;

void change_to_wireframe_rendering_mode() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void change_to_fill_rendering_mode() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

// clang-format off

float screen_verticies[] {
  1.0f, 1.0f, 0.0f,
  -1.0f, -1.0f, 0.0f,
  -1.0f, 1.0f, 0.0f,
  1.0f, -1.0f,  0.0f,
};

int screen_tris[] {
  0, 1, 2,
  0, 1, 3
};

// clang-format on

int main() {
  Engine::init();
  Engine::Window::create();
  Engine::Input::create_mapping(Engine::Input::Key{GLFW_KEY_SPACE, GLFW_PRESS},
                                change_to_wireframe_rendering_mode);
  Engine::Input::create_mapping(
      Engine::Input::Key{GLFW_KEY_SPACE, GLFW_RELEASE},
      change_to_fill_rendering_mode);

  auto shader = Engine::Draw::Shader("../assets/shaders/vert.vs",
                                     "../assets/shaders/frag.fs");

  u_int EBO, VAO, VBO;

  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(screen_verticies), screen_verticies,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(screen_tris), screen_tris,
               GL_STATIC_DRAW);

  while (!Engine::shouldClose()) {
    Engine::Input::proceed_input();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    shader.use();
    shader.setVec2("u_mouse", Engine::mousePos[0], Engine::mousePos[1]);
    shader.setFloat("u_time", glfwGetTime());
    shader.setVec2("u_resolution", Engine::WIDTH, Engine::HEIGHT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    Engine::tick();
  }
  Engine::terminate();
}
