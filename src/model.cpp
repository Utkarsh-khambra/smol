#include "model.hpp"
#include <array>
#include <charconv>
#include <fstream>
#include <glm/glm.hpp>
#include <ranges>

Model::Model() {}

// drop int is there because split view is not getting rid of extran space in vn
// and vt
// TODO handle errors reporting in from_char
static glm::vec3 parse_vert_props(std::string_view line, int drop_int = 1) {
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
  for (std::string line; std::getline(file, line);) {
    // Vertex parsing
    if (line.substr(0, 2) == "v ") {
      vertices.emplace_back(parse_vert_props(line));
    }
    // Texture parsing
    else if (line.substr(0, 2) == "vt") {
      texture.emplace_back(parse_vert_props(line, 2));
    }
    // Vertex Normal parsing
    else if (line.substr(0, 2) == "vn") {
      normals.emplace_back(parse_vert_props(line, 2));
    }
    // Face parsing
    else if (line.substr(0, 2) == "f ") {
      std::array<glm::uvec3, 3> temp_indices;
      int j = 0;
      for (auto i : line | std::views::split(' ') | std::views::drop(1)) {
        size_t k = 0;
        for (auto c : i | std::views::split('/')) {
          std::from_chars(&*std::ranges::begin(c),
                          &*std::ranges::begin(c) + std::ranges::distance(c),
                          temp_indices.at(k)[j]);
          temp_indices.at(k)[j] -= 1;
          assert(k < 3);
          ++k;
        }
        ++j;
      }
      faces.push_back(temp_indices);
    }
  }
}

size_t Model::nfaces() const noexcept { return faces.size(); }
size_t Model::nverts() const noexcept { return vertices.size(); }
glm::vec3 Model::vert(size_t id) noexcept { return vertices.at(id); }
glm::uvec3 Model::face(size_t id, FACE_PROP prop) noexcept {
  return faces.at(id).at(static_cast<size_t>(prop));
}
const glm::vec3 Model::vert(size_t id) const noexcept {
  return vertices.at(id);
}
const glm::uvec3 Model::face(size_t id, FACE_PROP prop) const noexcept {
  return faces.at(id).at(static_cast<size_t>(prop));
}
glm::vec3 Model::normal(size_t id) noexcept { return normals.at(id); }
glm::vec3 Model::normal(size_t id) const noexcept { return normals.at(id); }
glm::vec3 Model::texture_coord(size_t id) noexcept { return texture.at(id); }
glm::vec3 Model::texture_coord(size_t id) const noexcept {
  return texture.at(id);
}
