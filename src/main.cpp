#include "image.hpp"
#include "model.hpp"
#include "utils.hpp"
#include <cmath>
#include <fmt/core.h>
/* #include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/type_trait.hpp>
#include <numbers> */

/* int main1() {
  auto a = look_at(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  auto b =
      glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  fmt::print("Correct\n");
  for (auto i = 0; i < 4; ++i) {
    for (auto j = 0; j < 4; ++j)
      fmt::print("{} ", b[i][j]);
    fmt::print("\n");
  }

  auto proj = projection(90, 0.1, 100);
  glm::vec3 test(1, 2, 3);
  auto t = glm::vec4(test, 1) * proj;
  for (auto i = 0; i < 4; ++i)
    fmt::print("{} ", t[i]);
  if (a == b)
    fmt::print("\nWTF\n");
} */
int main() {
  Image skin_texture("../asset/african_head_diffuse.tga");
  Model m("/home/utkarsh/smol/asset/head.obj");
  auto I = render(m, skin_texture);
  I.write("test.jpg");
  system("display test.jpg");
  return 0;
}
