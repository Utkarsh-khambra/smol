#include "image.hpp"
#include <fmt/core.h>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>
const unsigned char *Image::get_data() const noexcept {
  return image_data.data();
}
int Image::x() const noexcept { return width; }
int Image::y() const noexcept { return height; }
void Image::set(int x, int y, glm::u8vec3 color) noexcept {
  if ((x < 0 || y < 0) || (x >= width || y >= height)) {
    spdlog::warn("({}, {}) pixel position is not good\n", x, y);
    return;
  }
  std::copy_n(glm::value_ptr(color), 3,
              image_data.begin() + (y * width + x) * channels);
}
