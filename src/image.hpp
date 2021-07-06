#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <algorithm>
#include <glm/glm.hpp>
#include <memory>
#include <span>
#include <type_traits>
#include <vector>
class Image {
public:
  Image();
  Image(int w, int h, int colors) noexcept;
  Image(const char *filename) noexcept;
  void set(int x, int y, glm::u8vec3 color) noexcept;
  void set(std::span<unsigned char> pixel_data) noexcept;
  int x() const noexcept;
  int y() const noexcept;
  const unsigned char *get_data() const noexcept;
  void write(const char *file, bool flip = true) const noexcept;
  glm::u8vec3 get_color(int x, int y) const noexcept;

private:
  std::vector<unsigned char> image_data;
  int width;
  int height;
  int channels;
};
#endif // IMAGE_HPP
