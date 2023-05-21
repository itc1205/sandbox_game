#include <core/mouse.hpp>

namespace Engine {
float mousePos[2] = {0.0f, 0.0f};
namespace Callbacks {
void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
  mousePos[0] = xpos;
  mousePos[1] = Engine::HEIGHT - ypos;
}
} // namespace Callbacks
} // namespace Engine