#include "image.hpp"
#include <algorithm>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

Image::Image() : image_data(), width(0), height(0), channels(0) {}
Image::Image(int w, int h, int color) noexcept
    : image_data(static_cast<size_t>(w * h * color)), width(w), height(h),
      channels(color) {}
Image::Image(const char *filename) noexcept {
  stbi_set_flip_vertically_on_load(1);
  auto temp = stbi_load(filename, &width, &height, &channels, 0);
  if (!temp) {
    spdlog::warn("Could not open file\n");
    return;
  }
  image_data.reserve(static_cast<size_t>(width * height * channels));
  // Expensive copy
  std::ranges::copy(temp, temp + width * height * channels,
                    std::back_insert_iterator(image_data));
  stbi_image_free(temp);
}
[[nodiscard]] const unsigned char *Image::get_data() const noexcept {
  return image_data.data();
}
[[nodiscard]] int Image::x() const noexcept { return width; }
[[nodiscard]] int Image::y() const noexcept { return height; }

void Image::set(int x, int y, glm::u8vec3 color) noexcept {
  if ((x < 0 || y < 0) || (x >= width || y >= height)) {
    spdlog::warn("({}, {}) pixel position is not good\n", x, y);
    return;
  }
  std::copy_n(glm::value_ptr(color), 3,
              image_data.begin() + (y * width + x) * channels);
}

void Image::set(std::span<unsigned char> pixel_data) noexcept {
  if (pixel_data.size() != static_cast<size_t>(width * height * channels)) {
    spdlog::warn("The passed pixel data is wrong");
    return;
  }
  std::copy_n(pixel_data.data(), pixel_data.size(), image_data.begin());
}

void Image::write(const char *file, bool flip) const noexcept {
  if (flip)
    stbi_flip_vertically_on_write(1);
  stbi_write_jpg(file, width, height, channels, image_data.data(), 90);
}

[[nodiscard]] glm::u8vec3 Image::get_color(int x, int y) const noexcept {
  assert(image_data.size() > 0);
  size_t index = static_cast<size_t>((y * width + x) * channels);
  return glm::u8vec3(image_data.at(index), image_data.at(index + 1),
                     image_data.at(index + 2));
}
