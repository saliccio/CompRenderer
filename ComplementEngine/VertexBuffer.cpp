#include "VertexBuffer.h"
#include "errorcheck.h"

namespace ComplementEngine {
	VertexBuffer::VertexBuffer(const void* data, unsigned int size)
	{
		E(glGenBuffers(1, &m_ID));
		E(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
		E(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	VertexBuffer::~VertexBuffer()
	{
		E(glDeleteBuffers(1, &m_ID));
	}

	void VertexBuffer::bind() const
	{
		E(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
	}

	void VertexBuffer::unbind()
	{
		E(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
}