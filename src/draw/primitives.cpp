#include "draw/primitives.hpp"

namespace Engine::Draw
{
    void draw_text(BitmapFont &bf, std::string &text, float x, float y)
    {
        draw_text(bf, text.c_str(), x, y);
    }

    void draw_text(BitmapFont &bf, std::string &text, float x, float y, glm::vec3 color)
    {
        draw_text(bf, text.c_str(), x, y, color);
    }

    void draw_text(BitmapFont &bf, std::string &text, float x, float y, float scale)
    {
        draw_text(bf, text.c_str(), x, y, scale);
    }

    void draw_text(BitmapFont &bf, std::string &text, float x, float y, float scale, glm::vec3 color)
    {
        draw_text(bf, text.c_str(), x, y, scale, color);
    }

    void draw_text(BitmapFont &bf, const char *text, float x, float y)
    {
        draw_text(bf, text, x, y, 1.f, glm::vec3(1.f, 1.f, 1.f));
    }
    
    void draw_text(BitmapFont &bf, const char *text, float x, float y, glm::vec3 color)
    {
        draw_text(bf, text, x, y, 1.f, glm::vec3(1.f, 1.f, 1.f));
    }

    void draw_text(BitmapFont &bf, const char *text, float x, float y, float scale)
    {
        draw_text(bf, text, x, y, scale, glm::vec3(1.f, 1.f, 1.f));
    }

    void draw_text(BitmapFont &bf, const char *text, float x, float y, float scale, glm::vec3 color)
    {
        bf.shader.use();
        bf.shader.setVec3("textColor", color);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(bf.VAO);

        for (int c = 0; c < strlen(text); c++)
        {
            Character ch = bf.Characters[text[c]];
            float xpos = x + ch.Bearing.x;
            float ypos = y - (ch.Size.y - ch.Bearing.y);

            float w = ch.Size.x;
            float h = ch.Size.y;

            // new VBO vertices
            float vertices[6][4] = {
                {xpos, ypos + h, 0.f, 0.f},
                {xpos, ypos, 0.f, 1.f},
                {xpos + w, ypos, 1.f, 1.f},

                {xpos, ypos + h, 0.f, 0.f},
                {xpos + w, ypos, 1.f, 1.f},
                {xpos + w, ypos + h, 1.f, 0.f},
            };
            // render glyph over the quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, bf.VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            x += (ch.Advance >> 6);
        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
} // namespace Engine::Draw
