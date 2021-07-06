#include "image.hpp"
#include "model.hpp"
#include "utils.hpp"
#include <fmt/core.h>
int main() {
  Image skin_texture("../asset/african_head_diffuse.png");
  Model m("/home/utkarsh/smol/asset/head.obj");
  auto I = render(m, skin_texture);
  I.write("test.jpg");
  system("display test.jpg");
  return 0;
}
