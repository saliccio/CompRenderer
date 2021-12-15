#pragma once

#include <glm/vec3.hpp>
#include <vector>
#include "Transform.h"

namespace CompRenderer {
	class Light {
	private:
		glm::vec3 m_LightColor;
		static std::vector<Light> lights;
	public:
		Transform transform;

		Light(const glm::vec3& lightColor, const Transform& transform);

		inline glm::vec3 getLightColor() const { return m_LightColor; }

		static unsigned int addLight(const Light& light);

		inline static Light& getLight(unsigned int index) { return lights[index]; }
	};
}