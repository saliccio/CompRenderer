#include <unordered_map>
#include "Texture.h"
#include "stb_image.h"

namespace CompRenderer {
	int Texture::textureUnitCount;

	std::unordered_map<std::string, Texture*> Texture::cachedTextures;

	Texture::Texture()
		: m_ID(-1)
	{

	}

	Texture::Texture(const std::string& filePath, const aiTextureType textureType)
		: m_Slot(-1), m_ID(-1), m_FilePath(filePath), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0), m_TextureType(textureType)
	{
		stbi_set_flip_vertically_on_load(1);
		m_LocalBuffer = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

		E(glGenTextures(1, &m_ID));
		E(glBindTexture(GL_TEXTURE_2D, m_ID));

		E(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		E(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		E(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		E(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		E(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));

		if (m_LocalBuffer != nullptr) {
			stbi_image_free(m_LocalBuffer);
		}

		E(glBindTexture(GL_TEXTURE_2D, 0));
	}

	Texture::~Texture()
	{
		E(glDeleteTextures(1, &m_ID));
	}

	void Texture::bind(unsigned int slot) const
	{
		m_Slot = slot;
		E(glActiveTexture(GL_TEXTURE0 + slot));
		E(glBindTexture(GL_TEXTURE_2D, m_ID));
	}

	void Texture::unbind()
	{
		E(glBindTexture(GL_TEXTURE_2D, 0));
	}

	bool Texture::operator==(const Texture& other) const
	{
		return m_ID == other.m_ID;
	}

	bool Texture::addTexture(const std::string& name, aiTextureType type)
	{
		if (cachedTextures.find(name) == cachedTextures.end()) {
			cachedTextures[name] = new Texture(name, type);
			return true;
		}
		return false;
	}

	Texture* Texture::getTexture(const std::string& name)
	{
		if (cachedTextures.find(name) != cachedTextures.end()) {
			return cachedTextures[name];
		}
		return nullptr;
	}
}