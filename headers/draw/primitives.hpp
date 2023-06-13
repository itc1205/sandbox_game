#pragma once

#include "core/font.hpp"

#include <string>

#include "glm/glm.hpp"

namespace Engine::Draw
{
    void draw_text(BitmapFont &bf, std::string &text, float x, float y);
    void draw_text(BitmapFont &bf, std::string &text, float x, float y, glm::vec3 color);
    void draw_text(BitmapFont &bf, std::string &text, float x, float y, float scale);
    void draw_text(BitmapFont &bf, std::string &text, float x, float y, float scale, glm::vec3 color);
    
    void draw_text(BitmapFont &bf, const char *text, float x, float y);
    void draw_text(BitmapFont &bf, const char *text, float x, float y, glm::vec3 color);
    void draw_text(BitmapFont &bf, const char *text, float x, float y, float scale);
    void draw_text(BitmapFont &bf, const char *text, float x, float y, float scale, glm::vec3 color);
} // namespace Engine::Draw
