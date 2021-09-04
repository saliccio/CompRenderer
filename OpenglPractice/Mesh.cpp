#include "Mesh.h"
#include "Model.h"

namespace ComplementEngine {
	void Mesh::setupMesh()
	{
		vertexArray.bind();

		VertexBufferC vertexBuffer(vertices.data(), vertices.size());
		vertexBuffer.bind();

		vertexArray.addBuffers(vertexBuffer);

		vertexArray.unbind();

		vertexBuffer.unbind();
	}

	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Material& material, Model* modelPtr)
		: vertices(vertices), indices(indices), indexBuffer(indices), material(material), m_ParentPtr(modelPtr)
	{
		setupMesh();
	}
}