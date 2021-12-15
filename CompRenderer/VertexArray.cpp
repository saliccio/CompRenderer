#include "VertexArray.h"
#include "errorcheck.h"

namespace CompRenderer {
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_ID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_ID);
	}

	VertexArray::VertexArray(const VertexArray& other)
	{
		glGenVertexArrays(1, &m_ID);
	}

	void VertexArray::operator=(const VertexArray& other)
	{
		glGenVertexArrays(1, &m_ID);
	}

	void VertexArray::bind() const
	{
		E(glBindVertexArray(m_ID));
	}

	void VertexArray::unbind()
	{
		E(glBindVertexArray(0));
	}

	void VertexArray::addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& vertexBufferLayout)
	{
		E(glBindVertexArray(m_ID));
		vertexBuffer.bind();

		const std::vector<VertexBufferLayoutElement>& vertexBufferLayoutElements = vertexBufferLayout.getElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < vertexBufferLayoutElements.size(); i++) {
			const VertexBufferLayoutElement& element = vertexBufferLayoutElements[i];
			E(glEnableVertexAttribArray(i));
			E(glVertexAttribPointer(i, element.count, element.type, element.normalized, vertexBufferLayout.getStride(), (void*)offset));
			offset += element.count * VertexBufferLayoutElement::getSizeOfType(element.type);
		}
	}

	void VertexArray::addBuffers(const VertexBufferC& vertexBuffer)		// add position, normal and texcoords
	{
		E(glBindVertexArray(m_ID));
		vertexBuffer.bind();

		E(glEnableVertexAttribArray(0));
		E(glEnableVertexAttribArray(1));
		E(glEnableVertexAttribArray(2));

		float stride = sizeof(float) * 8;

		E(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0)); // position
		E(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * 3))); // position
		E(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * 6))); // texture coordinates
	}
}