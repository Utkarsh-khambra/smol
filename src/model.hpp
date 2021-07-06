#ifndef MODEL_HPP
#define MODEL_HPP

#include <array>
#include <glm/glm.hpp>
#include <vector>

enum class FACE_PROP { VERTEX = 0, TEXTURE, NORMAL };
class Model {
public:
  Model();
  Model(const char *filename);
  size_t nfaces() const noexcept;
  size_t nverts() const noexcept;
  glm::vec3 vert(size_t id) noexcept;
  glm::vec3 normal(size_t id) noexcept;
  glm::vec3 texture_coord(size_t id) noexcept;
  glm::uvec3 face(size_t id, FACE_PROP prop) noexcept;

  const glm::vec3 vert(size_t id) const noexcept;
  glm::vec3 normal(size_t id) const noexcept;
  glm::vec3 texture_coord(size_t id) const noexcept;
  const glm::uvec3 face(size_t id, FACE_PROP prop) const noexcept;

private:
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec3> texture;
  std::vector<glm::vec3> normals;
  std::vector<std::array<glm::uvec3, 3>> faces;
};
#endif // MODEL_HPP
