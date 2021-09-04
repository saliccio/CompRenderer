#pragma once
#include "Texture.h"

using namespace ComplementEngine;
namespace ComplementEngine_ {
	class static_construction {
	private:
		static bool m_Constructed;

		void ConstructTexture() {
			Texture::addTexture(CGE_TEXTURE_NOTEXTURE_FILEPATH, aiTextureType::aiTextureType_DIFFUSE);

			E(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &Texture::textureUnitCount));
		}
	public:
		static_construction() {
			if (!m_Constructed) {
				ConstructTexture();
				m_Constructed = true;
			} else {
				ASSERT(false);
			}
		}
	};

	bool static_construction::m_Constructed = false;
}