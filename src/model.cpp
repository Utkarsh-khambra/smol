#include "model.hpp"
#include <charconv>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtx/io.hpp>
#include <iomanip>
#include <iostream>
#include <ranges>

Model::Model() {}
Model::Model(const char *filename) {
  std::ifstream file(filename);
  int j;
  for (std::string line; std::getline(file, line);) {
    if (line.substr(0, 2) == "v ") {
      glm::vec3 temp;
      j = 0;
      for (auto vert : line | std::views::split(' ') | std::views::drop(1)) {
        std::from_chars(
            &*std::ranges::begin(vert),
            &*std::ranges::begin(vert) + std::ranges::distance(vert), temp[j]);
        ++j;
      }
      vertices.push_back(temp);
    } else if (line.substr(0, 2) == "f ") {
      glm::uvec3 temp_coords;
      j = 0;
      for (auto i : line | std::views::split(' ') | std::views::drop(1)) {
        for (auto c : i | std::views::split('/')) {
          std::from_chars(&*std::ranges::begin(c),
                          &*std::ranges::begin(c) + std::ranges::distance(c),
                          temp_coords[j]);
          temp_coords[j] -= 1;
          ++j;
          break;
        }
      }
      faces.push_back(temp_coords);
    }
  }
}

size_t Model::nfaces() const noexcept { return faces.size(); }
size_t Model::nverts() const noexcept { return vertices.size(); }
glm::vec3 Model::vert(size_t id) noexcept { return vertices.at(id); }
glm::uvec3 Model::face(size_t id) noexcept { return faces.at(id); }
const glm::vec3 Model::vert(size_t id) const noexcept {
  return vertices.at(id);
}
const glm::uvec3 Model::face(size_t id) const noexcept { return faces.at(id); }
