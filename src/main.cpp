#include "core/engine.hpp"
#include "core/input.hpp"
#include "core/mouse.hpp"
#include "core/window.hpp"
#include "core/font.hpp"
#include "draw/shader.hpp"
#include "draw/texture.hpp"
#include "draw/primitives.hpp"

#include <GL/gl.h>
#include <GL/glext.h>
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <iostream>

#include <logger/logger.hpp>

void change_to_wireframe_rendering_mode()
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void change_to_fill_rendering_mode()
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main()
{
  Engine::init();
  Engine::Window::create();
  Engine::Input::create_mapping(Engine::Input::Key{GLFW_KEY_SPACE, GLFW_PRESS},
                                change_to_wireframe_rendering_mode);
  Engine::Input::create_mapping(
      Engine::Input::Key{GLFW_KEY_SPACE, GLFW_RELEASE},
      change_to_fill_rendering_mode);

  Engine::Font font("assets/fonts/VCR_OSD_MONO.ttf");
  Engine::BitmapFont bf = font.getBitmap();
  
  std::string text = "Test";

  while (!Engine::shouldClose())
  {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Engine::Draw::draw_text(bf, text.c_str(), 40.f, 40.f, 1.f, glm::vec3(1.f, 1.f, 1.f));
    Engine::Draw::draw_text(bf, "Fuck u", 100.f, 100.f, 1.f, glm::vec3(1.f, 1.f, 1.f));

    Engine::tick();
  }
  Engine::terminate();
}
