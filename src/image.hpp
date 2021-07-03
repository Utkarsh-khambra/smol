#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <algorithm>
#include <glm/glm.hpp>
#include <vector>
class Image {
public:
  Image() : image_data(), width(0), height(0), channels(0) {}
  Image(int w, int h, int colors) noexcept
      : image_data(static_cast<size_t>(w * h * colors), 0), width(w), height(h),
        channels(colors) {}
  void set(int x, int y, glm::u8vec3 color) noexcept;
  int x() const noexcept;
  int y() const noexcept;
  const unsigned char *get_data() const noexcept;

private:
  std::vector<unsigned char> image_data;
  int width;
  int height;
  int channels;
};
#endif // IMAGE_HPP
