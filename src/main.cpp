#include "drawing.hpp"
#include "image.hpp"
#include "model.hpp"
#include <cmath>
#include <cstdlib>
#include <fmt/core.h>
#include <random>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

constexpr int width = 700, height = 700;
std::random_device rd;
std::default_random_engine rng(rd());
std::uniform_int_distribution<unsigned char> nums(0, 255);

Image render_face(Model &model) {
  Image img(width, height, 3);
  for (auto i = 0ul; i < model.nfaces(); ++i) {
    auto f = model.face(i);
    glm::vec2 screnn_cords[3];
    for (auto j = 0; j < 3; ++j) {
      auto v = model.vert(f[j]);
      screnn_cords[j] =
          glm::vec2((v.x + 1.) * width / 2., (v.y + 1.) * height / 2.);
    }
    draw_triangle(screnn_cords[0], screnn_cords[1], screnn_cords[2], img,
                  {nums(rng), nums(rng), nums(rng)});
  }
  return img;
}

int main() {
  Model m("/home/utkarsh/smol/asset/head.obj");
  auto I = render_face(m);
  stbi_flip_vertically_on_write(1);
  stbi_write_jpg("test.jpg", I.x(), I.y(), 3, I.get_data(), 90);
  system("display test.jpg");
  return 0;
}
