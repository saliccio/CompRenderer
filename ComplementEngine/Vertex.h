#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace ComplementEngine {
	struct Vertex {
	public:
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};
}