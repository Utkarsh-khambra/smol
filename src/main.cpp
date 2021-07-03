#include "drawing.hpp"
#include "image.hpp"
#include "model.hpp"
#include <cmath>
#include <cstdlib>
#include <fmt/core.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

constexpr int widht = 700, height = 700;

Image render_face(Model &model) {
  Image img(widht, height, 3);
  for (auto i = 0ul; i < model.nfaces(); ++i) {
    auto f = model.face(i);
    for (auto j = 0; j < 3; ++j) {
      auto v0 = model.vert(f[j]);
      auto v1 = model.vert(f[(j + 1) % 3]);
      v0.x = (v0.x + 1.) * widht / 2.;
      v0.y = (v0.y + 1.) * height / 2.;
      v1.x = (v1.x + 1.) * widht / 2.;
      v1.y = (v1.y + 1.) * height / 2.;
      line(v0, v1, img, {255, 0, 0});
    }
  }
  return img;
}

int main() {
  Image I(widht, height, 3);
  glm::vec2 p{600, 50};
  glm::vec2 q{200, 650};
  glm::vec2 r{70, 346};
  draw_triangle(p, q, r, I, {0, 255, 0});
  stbi_flip_vertically_on_write(1);
  stbi_write_jpg("test.jpg", I.x(), I.y(), 3, I.get_data(), 90);
  system("display test.jpg");
  return 0;
}
