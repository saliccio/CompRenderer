#pragma once
#include <GL/glew.h>
#include "Vertex.h"

namespace ComplementEngine {
	class VertexBufferC {
	private:
		unsigned int m_ID;
	public:
		VertexBufferC(const Vertex* data, unsigned int elementCount);
		~VertexBufferC();

		void bind() const;
		static void unbind();
	};
}