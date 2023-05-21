#pragma once

#include <core/engine.hpp>

namespace Engine::Draw {
class Shader {
public:
  uint ID;
  Shader(const char *vertexPath, const char *fragmentPath);

  void use();

  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;

  void setFloat2(const std::string &name, float value[2]) const;
  void setFloat3(const std::string &name, float value[3]) const;
  void setFloat4(const std::string &name, float value[4]) const;

  void setInt2(const std::string &name, int value[2]) const;
};
} // namespace Engine::Draw
  // namespace Engine::Draw