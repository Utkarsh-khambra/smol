#include "image.hpp"
#include <fmt/core.h>
#include <spdlog/spdlog.h>
const unsigned char *Image::get_data() const noexcept {
  return image_data.data();
}
int Image::x() const noexcept { return width; }
int Image::y() const noexcept { return height; }
void Image::set(int x, int y, Color color) noexcept {
  if ((x < 0 || y < 0) || (x >= width || y >= height)) {
    spdlog::warn("({}, {}) pixel position is not good\n", x, y);
    return;
  }
  std::copy_n(color.begin(), color.size(),
              image_data.begin() + (y * width + x) * channels);
}
