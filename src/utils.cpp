#include "utils.hpp"
#include "drawing.hpp"
#include <fmt/core.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>
static constexpr int width = 700, height = 700;
glm::vec3 light_dir(0, 0, -1);
static constexpr int c = -3;

// function to genrate view matrix
glm::mat4 look_at(glm::vec3 camera, glm::vec3 target, glm::vec3 camera_up) {
  glm::mat4 view(1.0);
  auto z = glm::normalize(camera - target);
  auto x = glm::normalize(glm::cross(camera_up, z));
  auto y = glm::normalize(glm::cross(z, x));
  view = glm::column(view, 0, {x, 0.0});
  view = glm::column(view, 1, {y, 0.0});
  view = glm::column(view, 2, {z, 0.0});
  view = glm::column(view, 3, glm::vec4(-camera, 1.0));
  return view;
}

// Function to generate projection matrix
// TODO fix bug in this function
glm::mat4 projection(const float view_angle, float aspect, const float near,
                     const float far) {
  auto top = near / std::tan(view_angle * std::numbers::pi / 360);
  auto bottom = -top;
  auto right = top * aspect;
  auto left = -right;
  glm::mat4 ret(1.0);
  ret[0][0] = 2 * near / (right - left);
  ret[1][1] = 2 * near / (top - bottom);
  ret[0][2] = (right + left) / (right - left);
  ret[1][2] = (top + bottom) / (top - bottom);
  ret[2][2] = -(far + near) / (far - near);
  ret[2][3] = -1;
  ret[3][3] = 0;
  ret[3][2] = -(2 * far * near) / (far - near);
  return ret;
}

// The main function which should handle all rendering aspects
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
    // Calculates trianlgle normal to apply shading
    auto triangle_normal =
        glm::normalize(glm::cross((world_coords[2] - world_coords[0]),
                                  (world_coords[1] - world_coords[0])));
    auto intensity = glm::dot(triangle_normal, light_dir);

    // Only visible parts should be rendered
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
