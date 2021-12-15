#pragma once
#include <memory>
#include "Texture.h"
#include "Light.h"

namespace CompRenderer {
	// TODO: ADD VARIOUS DESTRUCTORS
	class Shader;

	class MaterialProperties {		// temporary, no heap deallocation
	private:
		Texture* m_DiffuseTexture;
		Texture* m_SpecularTexture;
	public:

		glm::vec3 ambientColor;
		glm::vec3 diffuseColor;
		glm::vec3 specularColor;

		//float ambientFactor;
		//float diffuseFactor;
		//float specularFactor;			they are related to light sources

		float shininess;

		float opacity;

		MaterialProperties();

		MaterialProperties(Texture* diffuseTexture, Texture* specularTexture = Texture::getTexture(CGE_TEXTURE_NOTEXTURE_FILEPATH));

		inline const Texture* const getDiffuseTexture() const { return m_DiffuseTexture; }
		inline const Texture* const getSpecularTexture() const { return m_SpecularTexture; }

		inline void setDiffuseTexture(Texture* value) {
			m_DiffuseTexture = value;
		}

		inline void setSpecularTexture(Texture* value) {
			m_SpecularTexture = value;
		}

		void bindTextures(unsigned int diffuseSlot = 0U, unsigned int specularSlot = 1U) const;
	};

	class Material {
	private:
		Shader* m_Shader;
		MaterialProperties m_Properties;
	public:
		Material() = default;
		Material(Shader* shader, const MaterialProperties& properties);
		
		inline const Shader* getShader() const { return m_Shader; }
		inline MaterialProperties& getProperties() { return m_Properties; }
	
		void bind(const glm::mat4& modelMatrix, const glm::mat4& viewProjectionMatrix, unsigned int diffuseSlot, unsigned int specularSlot = 1U);
	};
}