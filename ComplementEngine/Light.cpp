#include "Light.h"

namespace ComplementEngine {
	std::vector<Light> Light::lights;

	Light::Light(const glm::vec3& lightColor, const Transform& transform)
		: m_LightColor(lightColor), transform(transform)
	{
		
	}

	unsigned int Light::addLight(const Light& light)
	{
		lights.push_back(light);
		return lights.size() - 1;
	}
}
