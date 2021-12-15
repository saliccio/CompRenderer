#pragma once
#include <GL/glew.h>
#include "VertexBuffer.h"
#include "VertexBufferC.h"
#include "VertexBufferLayout.h"

namespace CompRenderer {
	class VertexArray {
	private:
		unsigned int m_ID;
	public:
		VertexArray();
		~VertexArray();
		VertexArray(const VertexArray& other);
		
		void operator=(const VertexArray& other);

		void bind() const;
		static void unbind();

		void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& vertexBufferLayout);
		void addBuffers(const VertexBufferC& vertexBuffer);
	};
}