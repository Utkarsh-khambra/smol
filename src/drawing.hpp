#ifndef DRAWING_HPP
#define DRAWING_HPP
#include "image.hpp"
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
void draw_triangle(glm::ivec2 p, glm::ivec2 q, glm::ivec2 r, glm::vec3 z_val,
                   Image &img, glm::u8vec3 color_p, glm::u8vec3 color_q,
                   glm::u8vec3 color_r, float *zbuffer);
void line(glm::vec2 p, glm::vec2 q, Image &img, glm::u8vec3 color);

class triangle {
public:
  triangle(glm::vec3 p, glm::vec3 q, glm::vec3 r, glm::u8vec3 color_p,
           glm::u8vec3 color_q, glm::u8vec3 color_r);

private:
  std::array<glm::vec3, 3> verts;
  std::array<glm::u8vec3, 3> color;
};
#endif // DRAWING_HPP
