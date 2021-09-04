#include "Material.h"
#include "Shader.h"

namespace ComplementEngine {
	Material::Material(Shader* shader, const MaterialProperties& properties)
		: m_Shader(shader), m_Properties(properties)
	{

	}

	void Material::bind(const glm::mat4& modelMatrix, const glm::mat4& viewProjectionMatrix, unsigned int diffuseSlot, unsigned int specularSlot)
	{
		m_Shader->bind();
		m_Shader->setUniformPhongMaterial(m_Properties, Light::getLight(0), modelMatrix, viewProjectionMatrix);
		m_Properties.bindTextures(diffuseSlot, specularSlot);
	}

	MaterialProperties::MaterialProperties()
		: m_DiffuseTexture(new Texture(CGE_TEXTURE_NOTEXTURE_FILEPATH, aiTextureType::aiTextureType_DIFFUSE)), m_SpecularTexture(new Texture(CGE_TEXTURE_NOTEXTURE_FILEPATH, aiTextureType::aiTextureType_SPECULAR)), ambientColor(1,1,1), diffuseColor(1, 1, 1), specularColor(1, 1, 1), opacity(1.0f), shininess(0.3f)
	{

	}

	MaterialProperties::MaterialProperties(Texture* diffuseTexture, Texture* specularTexture)
		: m_DiffuseTexture(diffuseTexture), m_SpecularTexture(specularTexture), ambientColor(1, 1, 1), diffuseColor(1, 1, 1), specularColor(1, 1, 1), opacity(1.0f), shininess(0.3f)
	{

	}

	void MaterialProperties::bindTextures(unsigned int diffuseSlot, unsigned int specularSlot) const
	{
		m_DiffuseTexture->bind(diffuseSlot);
		m_SpecularTexture->bind(specularSlot);
	}
}