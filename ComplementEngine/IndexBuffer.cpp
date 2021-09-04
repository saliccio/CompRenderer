#include "IndexBuffer.h"

namespace ComplementEngine {
	IndexBuffer::IndexBuffer(const std::vector<unsigned int>& data)
		: m_Size(data.size() * sizeof(unsigned int))
	{
		E(glGenBuffers(1, &m_ID));
		E(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
		E(glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), data.data(), GL_STATIC_DRAW));
	}

	IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int size)
		: m_Size(size)
	{
		E(glGenBuffers(1, &m_ID));
		E(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
		E(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	IndexBuffer::~IndexBuffer()
	{
		E(glDeleteBuffers(1, &m_ID));
	}

	void IndexBuffer::bind() const
	{
		E(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
	}

	void IndexBuffer::unbind()
	{
		E(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
}