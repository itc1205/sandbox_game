#pragma once
#include <glad/glad.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#include <core/input.hpp>
#include <core/window.hpp>
#include <logger/logger.hpp>

namespace Engine {

extern uint WIDTH, HEIGHT;

const auto TITLE = "The sandbox game";

extern GLFWwindow *window;

void init();
void setup_callbacks();
int exit_with_error(int error);
void tick();
bool shouldClose();
void terminate();

} // namespace Engine