#include "model.hpp"
#include <charconv>
#include <fmt/core.h>
#include <fstream>
#include <glm/glm.hpp>
#include <ranges>

Model::Model() {}

// drop int is there because split view is not getting rid of extran space in vn
// and vt
// TODO handle errors reporting in from_char
glm::vec3 parse_vert_props(std::string_view line, int drop_int = 1) {
  int j = 0;
  glm::vec3 temp;
  for (auto vert :
       line | std::views::split(' ') | std::views::transform([](auto &&rng) {
         return std::string_view(
             &*rng.begin(), static_cast<size_t>(std::ranges::distance(rng)));
       }) | std::views::drop(drop_int)) {
    std::from_chars(vert.begin(), vert.end(), temp[j]);
    ++j;
  }
  return temp;
}

Model::Model(const char *filename) {
  std::ifstream file(filename);
  int j;
  for (std::string line; std::getline(file, line);) {
    // Vertex parsing
    if (line.substr(0, 2) == "v ") {
      vertices.emplace_back(parse_vert_props(line));
    }
    // Texture parsing
    else if (line.substr(0, 2) == "vt") {
      texture_coord.emplace_back(parse_vert_props(line, 2));
    }
    // Vertex Normal parsing
    else if (line.substr(0, 2) == "vn") {
      normals.emplace_back(parse_vert_props(line, 2));
    }
    // Face parsing
    else if (line.substr(0, 2) == "f ") {
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
