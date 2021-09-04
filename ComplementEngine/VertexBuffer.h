#pragma once
#include <GL/glew.h>

namespace ComplementEngine {
	class VertexBuffer {
	private:
		unsigned int m_ID;
	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void bind() const;
		static void unbind();
	};
}