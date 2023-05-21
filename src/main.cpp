#include "core/engine.hpp"
#include "core/input.hpp"
#include "core/mouse.hpp"
#include "core/window.hpp"
#include "draw/shader.hpp"
#include "draw/texture.hpp"
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

// clang-format off

std::vector<float> vertices = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
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
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(),
               vertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(VAO);
  shader.use();

  auto wood_texture = Engine::Draw::Texture("../assets/wood.jpg", GL_RGB);
  auto face_texture = Engine::Draw::Texture("../assets/face.png", GL_RGBA);

  wood_texture.use();
  face_texture.use();

  while (!Engine::shouldClose()) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    float timeValue = glfwGetTime();
    shader.setFloat("u_time", timeValue);
    shader.setFloat2("u_mouse", Engine::mousePos);
    float res[2] = {float(Engine::WIDTH), float(Engine::HEIGHT)};
    shader.setFloat2("u_res", res);
    // render container

    shader.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    Engine::tick();
  }
  Engine::terminate();
}
