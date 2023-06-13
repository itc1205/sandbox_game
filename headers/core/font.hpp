#pragma once

#include <string>
#include <map>

#include <logger/logger.hpp>
#include <draw/shader.hpp>

#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace Engine
{
    struct Character {
        unsigned int TextureID;
        glm::ivec2 Size; // Size of glyph
        glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
        unsigned int Advance; // Offset to advance to next glyph
    };

     struct BitmapFont {
        std::map<char, Character> Characters;
        unsigned int VAO, VBO;
        Draw::Shader shader;
    };

    class Font {
        private:
            FT_Library ft = nullptr;
            FT_Face face = nullptr;
            unsigned int VAO, VBO;
            glm::mat4 projection;
            Draw::Shader shader;
            std::map<char, Character> Characters;

        public:
            Font(const char* path);
            BitmapFont getBitmap();
            ~Font();
    };    
} // namespace Engine
