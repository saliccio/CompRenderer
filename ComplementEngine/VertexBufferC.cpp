#include "VertexBufferC.h"
#include "errorcheck.h"

namespace ComplementEngine {
	VertexBufferC::VertexBufferC(const Vertex* data, unsigned int elementCount)
	{
		E(glGenBuffers(1, &m_ID));
		E(glBindBuffer(GL_ARRAY_BUFFER, m_ID));

		unsigned int count = elementCount * 8;

		float* bufferData = new float[count];
		unsigned int bufferDataOffset = 0;

		for (unsigned int i = 0; i < elementCount; i++) {
			glm::vec3 position = data[i].Position;
			glm::vec3 normal = data[i].Normal;
			glm::vec2 texCoords = data[i].TexCoords;

			bufferData[bufferDataOffset] = position.x;
			bufferData[bufferDataOffset + 1] = position.y;
			bufferData[bufferDataOffset + 2] = position.z;
			bufferData[bufferDataOffset + 3] = normal.x;
			bufferData[bufferDataOffset + 4] = normal.y;
			bufferData[bufferDataOffset + 5] = normal.z;
			bufferData[bufferDataOffset + 6] = texCoords.x;
			bufferData[bufferDataOffset + 7] = texCoords.y;

			bufferDataOffset += 8;
		}

		E(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count, bufferData, GL_STATIC_DRAW));

		delete[] bufferData;
	}

	VertexBufferC::~VertexBufferC()
	{
		E(glDeleteBuffers(1, &m_ID));
	}

	void VertexBufferC::bind() const
	{
		E(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
	}

	void VertexBufferC::unbind()
	{
		E(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
}