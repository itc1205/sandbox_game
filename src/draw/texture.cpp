#include <draw/texture.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Engine::Draw
{
  int _texture_number = 0;
  Texture::Texture(const std::string path_to_texture, int mode)
  {
    NT = _texture_number;
    _texture_number++;
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    // set the texture wrapping/filtering options (on the currently bound texture
    // object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char *data =
        stbi_load(path_to_texture.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, mode,
                   GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
      Logger::error("Could not load texture!");
    }
    stbi_image_free(data);
  }
  void Texture::use()
  {
    glActiveTexture(GL_TEXTURE0 + NT);
    glBindTexture(GL_TEXTURE_2D, ID);
  }
} // namespace Engine::Draw