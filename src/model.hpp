#ifndef WAVE_OBJ_HPP
#define WAVE_OBJ_HPP
#include <array>
#include <glm/glm.hpp>
#include <vector>
class Model {
public:
  Model();
  Model(const char *filename);
  size_t nfaces() const noexcept;
  size_t nverts() const noexcept;
  glm::vec3 vert(size_t id) noexcept;
  glm::uvec3 face(size_t id) noexcept;

  const glm::vec3 vert(size_t id) const noexcept;
  const glm::uvec3 face(size_t id) const noexcept;

private:
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec3> texture_coord;
  std::vector<glm::vec3> normals;
  std::vector<glm::uvec3> faces;
};
#endif // WAVE_OBJ_HPP
