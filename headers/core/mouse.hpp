#pragma once
#include <core/engine.hpp>

namespace Engine
{
    extern float mousePos[2];
    namespace Callbacks
    {
        void mouseCallback(GLFWwindow *window, double xpos, double ypos);
    } // namespace Callbacks
} // namespace Engine