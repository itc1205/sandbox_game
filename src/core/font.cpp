#include "core/font.hpp"

namespace Engine
{
    Font::Font(const char *path)
    {
        if (FT_Init_FreeType(&ft))
        {
            Logger::error("Could not init freetype library.");
            return;
        }

        if (FT_New_Face(ft, path, 0, &face))
        {
            Logger::error("Could not load font: " + std::string(path));
            return;
        }

        FT_Set_Pixel_Sizes(face, 0, 48);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for (unsigned char c = 0; c < 128; c++)
        {
            // load character glyph
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                Logger::error("Failed to load glyph");
            }

            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer);

            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // Store character for later use
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)};
            Characters.insert(std::pair<char, Character>(c, character));
        }

        shader = Draw::Shader("assets/shaders/text.vs", "assets/shaders/text.fs");
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        projection = glm::ortho(0.f, 800.f, 0.f, 600.f);
        shader.use();
        shader.setMat4("projection", projection);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    BitmapFont Font::getBitmap() {
        return BitmapFont {
            Characters,
            VAO, VBO,
            shader
        };
    }

    Font::~Font()
    {
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }
} // namespace Engine
