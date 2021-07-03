#ifndef DRAWING_HPP
#define DRAWING_HPP
#include "image.hpp"
#include <glm/glm.hpp>
void draw_triangle(glm::ivec2 p, glm::ivec2 q, glm::ivec2 r, Image &img,
                   glm::u8vec3 color);
void line(glm::vec2 p, glm::vec2 q, Image &img, glm::u8vec3 color);
#endif // DRAWING_HPP
