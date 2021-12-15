#pragma once
#include <assimp/scene.h>
#include "Renderer.h"

#define CGE_TEXTURE_NOTEXTURE_FILEPATH "no_texture.png"

namespace CompRenderer_ {
	class static_construction;	// Forward declaration
}

namespace CompRenderer {
	class Texture {
	private:
	    mutable unsigned int m_Slot;
	    unsigned int m_ID;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer; // be careful about move semantics
		int m_Width, m_Height, m_BPP;
		aiTextureType m_TextureType;

		static int textureUnitCount;

		static std::unordered_map<std::string, Texture*> cachedTextures;

		friend class CompRenderer_::static_construction;
	public:
		enum SpecialTexture{ NoTexture };

		Texture();
		Texture(const std::string& filePath, const aiTextureType textureType);
		Texture(const Texture& other) = default;
		Texture(Texture&& other) = default;
		~Texture();
		Texture& operator = (const Texture& other) = default;
		Texture& operator = (Texture&& other) = default;

		void bind(unsigned int slot = 0) const;
		static void unbind();

		bool operator==(const Texture& other) const;

		inline int getSlot() const { return m_Slot; }

		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }
		inline aiTextureType getTextureType() const { return m_TextureType; }
		inline unsigned int getTextureUnitCount() const { return textureUnitCount; }

		static bool addTexture(const std::string& filePath, aiTextureType type);
		static Texture* getTexture(const std::string& name);
	};
}