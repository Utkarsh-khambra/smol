#include "drawing.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <fmt/core.h>
#include <fmt/ranges.h>
void draw_triangle(glm::ivec2 p, glm::ivec2 q, glm::ivec2 r, glm::vec3 z_val,
                   Image &img, glm::u8vec3 color, float *zbuffer) {
  if (p.y == q.y && p.y == r.y)
    return;
  if (p.y > q.y)
    std::swap(p, q);
  if (p.y > r.y)
    std::swap(p, r);
  if (q.y > r.y)
    std::swap(q, r);
  int total_height = r.y - p.y;
  for (auto i = 0; i < total_height; ++i) {
    bool second_half = i > (q.y - p.y) || p.y == q.y;
    int segment_height = second_half ? r.y - q.y : q.y - p.y;
    auto alpha = static_cast<float>(i) / total_height;
    auto beta = static_cast<float>(i - (second_half ? (q.y - p.y) : 0)) /
                segment_height;
    glm::ivec2 a{std::lerp(p.x, r.x, alpha), std::lerp(p.y, r.y, alpha)};
    glm::ivec2 b =
        second_half
            ? glm::ivec2{std::lerp(q.x, r.x, beta), std::lerp(q.y, r.y, beta)}
            : glm::ivec2{std::lerp(p.x, q.x, beta), std::lerp(p.y, q.y, beta)};
    float a_z = std::lerp(z_val[0], z_val[2], alpha);
    float b_z = second_half ? std::lerp(z_val[1], z_val[2], beta)
                            : std::lerp(z_val[0], z_val[1], beta);

    if (a.x > b.x)
      std::swap(a, b);
    for (int j = a.x; j <= b.x; ++j) {
      auto z = std::lerp(a_z, b_z, static_cast<float>(j - a.x) / (b.x - a.x));
      if (zbuffer[(p.y + i) * img.x() + j] < z) {
        zbuffer[(p.y + i) * img.x() + j] = z;
        img.set(j, p.y + i, color);
      }
    }
  }
}

void line(glm::vec2 p, glm::vec2 q, Image &img, glm::u8vec3 color) {
  bool steep = false;
  if (std::abs(p.x - q.x) < std::abs(p.y - q.y)) {
    std::swap(p.x, p.y);
    std::swap(q.x, q.y);
    steep = true;
  }
  if (p.x > q.x) {
    std::swap(p.x, q.x);
    std::swap(p.y, q.y);
  }
  for (int x = p.x; x <= q.x; x++) {
    auto t = (x - p.x) / static_cast<float>(q.x - p.x);
    auto y = std::lerp(p.y, q.y, t);
    if (steep) {
      img.set(y, x, color);
    } else {
      img.set(x, y, color);
    }
  }
}
