#include "image.hpp"
#include <fmt/core.h>
const unsigned char *Image::get_data() const noexcept {
  return image_data.data();
}
int Image::x() const noexcept { return width; }
int Image::y() const noexcept { return height; }
bool Image::set(int x, int y, Color color) noexcept {
  if ((x < 0 || y < 0) || (x >= width || y >= height)) {
    if (x < 0 || y < 0)
      fmt::print("Negative\n");
    if (x >= width || y >= height)
      fmt::print("Big {} {}\n", x, y);
    return false;
  }
  std::copy_n(color.begin(), color.size(),
              image_data.begin() + (y * width + x) * channels);
  return true;
}
