#include "drawing.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <fmt/core.h>
#include <fmt/ranges.h>
void draw_triangle(glm::vec2 p, glm::vec2 q, glm::vec2 r, Image &img,
                   glm::u8vec3 color) {
  if (p.y > q.y)
    std::swap(p, q);
  if (p.y > r.y)
    std::swap(p, r);
  if (q.y > r.y)
    std::swap(q, r);
  int total_height = r.y - p.y;
  for (auto i = 0; i < total_height; ++i) {
    bool second_half = i > static_cast<int>(q.y - p.y) ||
                       static_cast<int>(r.y) == static_cast<int>(q.y);
    int segment_height = second_half ? r.y - q.y : q.y - p.y;
    auto alpha = static_cast<float>(i) / total_height;
    auto beta = static_cast<float>(i - (second_half ? (q.y - p.y) : 0)) /
                segment_height;
    glm::vec2 a = p + (r - p) * alpha;
    glm::vec2 b = second_half ? q + (r - q) * beta : p + (q - p) * beta;
    if (a.x > b.x)
      std::swap(a, b);
    for (int j = a.x; j <= b.x; ++j)
      img.set(j, p.y + i, color);
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
