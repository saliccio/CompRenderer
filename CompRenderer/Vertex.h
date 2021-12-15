#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace CompRenderer {
	struct Vertex {
	public:
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};
}