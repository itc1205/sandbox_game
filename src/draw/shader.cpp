#include <draw/shader.hpp>
#include <logger/logger.hpp>

#include <fstream>
#include <sstream>

namespace Engine::Draw
{
  Shader::Shader(const char *vertexPath, const char *fragmentPath)
  {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
      vShaderFile.open(vertexPath);
      fShaderFile.open(fragmentPath);

      std::stringstream vShaderStream, fShaderStream;

      vShaderStream << vShaderFile.rdbuf();
      fShaderStream << fShaderFile.rdbuf();

      vShaderFile.close();
      fShaderFile.close();

      vertexCode = vShaderStream.str();
      fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
      Logger::error("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ::CAUSE::" +
                    std::string(e.what()));
    }

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(vertex, 512, NULL, infoLog);
      Logger::warn("SHADER::VERTEX::COMPILATION_FAILED\n" + std::string(infoLog));
    };

    // similiar for Fragment Shader

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(fragment, 512, NULL, infoLog);
      Logger::warn("SHADER::FRAGMENT::COMPILATION_FAILED\n" +
                   std::string(infoLog));
    };

    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, fragment);
    glAttachShader(ID, vertex);
    glLinkProgram(ID);
    // print linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(ID, 512, NULL, infoLog);
      Logger::warn("SHADER::PROGRAM::LINKING_FAILED\n" + std::string(infoLog));
    }

    // delete the shaders as they're linked into our program now and no longer
    // necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
  }
  void Shader::use() { glUseProgram(ID); }

  void Shader::setBool(const std::string &name, bool value) const
  {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
  }
  void Shader::setFloat(const std::string &name, float value) const
  {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
  }

  void Shader::setInt(const std::string &name, int value) const
  {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
  }

  void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
  {
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
  }
  void Shader::setVec2(const std::string &name, float x, float y) const
  {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
  }

  void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
  {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
  }
  void Shader::setVec3(const std::string &name, float x, float y, float z) const
  {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
  }

  void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
  {
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
  }
  void Shader::setVec4(const std::string &name, float x, float y, float z,
                       float w) const
  {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
  }

  void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
  {
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                       &mat[0][0]);
  }

  void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
  {
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                       &mat[0][0]);
  }

  void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
  {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                       &mat[0][0]);
  }

} // namespace Engine::Draw