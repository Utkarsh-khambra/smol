#include "utils.hpp"
#include "drawing.hpp"
#include <fmt/core.h>
#include <glm/glm.hpp>
static constexpr int width = 700, height = 700;
glm::vec3 light_dir(0, 0, -1);
static constexpr int c = -3;

Image render(const Model &model, const Image &texture) {
  Image img(width, height, 3);
  float zbuffer[width * height];
  std::fill(zbuffer, zbuffer + width * height,
            -std::numeric_limits<float>::max());
  for (auto i = 0ul; i < model.nfaces(); ++i) {
    auto f = model.face(i, FACE_PROP::VERTEX);
    auto ft = model.face(i, FACE_PROP::TEXTURE);
    glm::ivec2 screen_cords[3];
    glm::u8vec3 vert_colors[3];
    glm::vec3 world_coords[3];
    for (auto j = 0; j < 3; ++j) {
      auto v = model.vert(f[j]);
      auto texc = model.texture_coord(ft[j]);
      screen_cords[j] =
          glm::ivec2((v.x + 1.) * width / 2., (v.y + 1.) * height / 2.);
      world_coords[j] = v;
      auto temp = glm::ivec2(static_cast<float>(texc.x) * texture.x(),
                             static_cast<float>(texc.y) * texture.y());
      vert_colors[j] = texture.get_color(temp.x, temp.y);
    }
    auto triangle_normal =
        glm::normalize(glm::cross((world_coords[2] - world_coords[0]),
                                  (world_coords[1] - world_coords[0])));
    auto intensity = glm::dot(triangle_normal, light_dir);
    if (intensity > 0) {
      for (auto j = 0; j < 3; ++j)
        vert_colors[j] =
            glm::u8vec3(static_cast<float>(intensity * vert_colors[j].x),
                        static_cast<float>(intensity * vert_colors[j].y),
                        static_cast<float>(intensity * vert_colors[j].z));
      draw_triangle(
          screen_cords[0], screen_cords[1], screen_cords[2],
          glm::vec3(world_coords[0].z, world_coords[1].z, world_coords[2].z),
          img, vert_colors[0], vert_colors[1], vert_colors[2], zbuffer);
    }
  }
  return img;
}
