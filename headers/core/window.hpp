#pragma once
#include <core/engine.hpp>

namespace Engine::Window {
GLFWwindow *create();
}
namespace Engine::Callbacks {
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
}
