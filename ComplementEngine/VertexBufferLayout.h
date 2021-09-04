#pragma once
#include <vector>
#include <GL/glew.h>

namespace ComplementEngine {
	struct VertexBufferLayoutElement {
		unsigned int type;
		unsigned int count;
		bool normalized;

		static unsigned int getSizeOfType(unsigned int type) {
			switch (type) {
			case GL_INT:
				return sizeof(GLint);
			case GL_UNSIGNED_INT:
				return sizeof(GLuint);
			case GL_UNSIGNED_BYTE:
				return sizeof(GLubyte);
			case GL_FLOAT:
				return sizeof(GLfloat);
			}
		}
	};

	class VertexBufferLayout {
	private:
		unsigned int m_Stride;
		std::vector<VertexBufferLayoutElement> m_Elements;
	public:
		VertexBufferLayout()
			: m_Stride(0)
		{

		}

		template <typename T>
		void Add(unsigned int count) {
			static_assert(false);
		}

		template <>
		void Add<unsigned int>(unsigned int count) {
			m_Elements.push_back({ GL_UNSIGNED_INT, count, false });
			m_Stride += VertexBufferLayoutElement::getSizeOfType(GL_UNSIGNED_INT) * count;
		}

		template <>
		void Add<unsigned char>(unsigned int count) {
			m_Elements.push_back({ GL_UNSIGNED_BYTE, count, true });
			m_Stride += VertexBufferLayoutElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
		}

		template <>
		void Add<float>(unsigned int count) {
			m_Elements.push_back({ GL_FLOAT, count, false });
			m_Stride += VertexBufferLayoutElement::getSizeOfType(GL_FLOAT) * count;
		}

		inline unsigned int getStride() const {
			return m_Stride;
		}

		inline const std::vector<VertexBufferLayoutElement>& getElements() const {
			return m_Elements;
		}
	};
}