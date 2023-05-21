#include "core/engine.hpp"
#include "core/input.hpp"
#include "core/window.hpp"
#include "draw/shader.hpp"
#include <GL/gl.h>
#include <GL/glext.h>
#include <glad/glad.h>

#include <GLFW/glfw3.h>



#include <iostream>

#include <logger/logger.hpp>

void change_to_wireframe_rendering_mode() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void change_to_fill_rendering_mode() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

float verticies[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

float texCoords[] = {0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f};

int main() {
  Engine::init();
  Engine::Window::create();
  Engine::Input::create_mapping(Engine::Input::Key{GLFW_KEY_SPACE, GLFW_PRESS},
                                change_to_wireframe_rendering_mode);
  Engine::Input::create_mapping(
      Engine::Input::Key{GLFW_KEY_SPACE, GLFW_RELEASE},
      change_to_fill_rendering_mode);

  auto shader = Engine::Draw::Shader("", "");
  uint VAO;
  glGenVertexArrays(1, &VAO);

  uint VBO;
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(VAO);
  shader.use();

  while (!Engine::shouldClose()) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float timeValue = glfwGetTime();
    glBindVertexArray(
        VAO); // seeing as we only have a single VAO there's no need to bind it
              // every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);

    Engine::tick();
  }
  Engine::terminate();
}
