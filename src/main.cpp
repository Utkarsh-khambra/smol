#include "image.hpp"
#include "model.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fmt/core.h>
#include <unistd.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

constexpr int widht = 700, height = 700;

void line(glm::ivec2 p0, glm::ivec2 p1, Image &img) {
  bool steep = false;
  std::array<unsigned char, 3> color{255, 255, 255};
  if (std::abs(p0.x - p1.x) < std::abs(p0.y - p1.y)) {
    std::swap(p0.x, p0.y);
    std::swap(p1.x, p1.y);
    steep = true;
  }
  if (p0.x > p1.x) {
    std::swap(p0.x, p1.x);
    std::swap(p0.y, p1.y);
  }
  for (int x = p0.x; x <= p1.x; x++) {
    auto t = (x - p0.x) / static_cast<float>(p1.x - p0.x);
    auto y = std::lerp(p0.y, p1.y, t);
    if (steep) {
      img.set(y, x, color);
    } else {
      img.set(x, y, color);
    }
  }
}
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
      line(v0, v1, img);
    }
  }
  return img;
}

int main() {
  Model m("/home/utkarsh/smol/src/head.obj");
  auto I = render_face(m);
  stbi_flip_vertically_on_write(1);
  stbi_write_jpg("test.jpg", I.x(), I.y(), 3, I.get_data(), 90);
  system("display test.jpg");
  return 0;
}
