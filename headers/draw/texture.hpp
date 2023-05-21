#pragma once

#include <core/engine.hpp>

namespace Engine::Draw {
extern int _texture_number;
class Texture {
public:
  int NT; // Number of texture;
  uint ID;
  Texture(const std::string path_to_texture, int mode);
  void use();
};
} // namespace Engine::Draw
