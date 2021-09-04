#include "Renderer.h"
#include "Shader.h"
#include "Mesh.h"
#include "Model.h"

namespace ComplementEngine {

	void Renderer::calculateVP(const glm::mat4& newViewMatrixValue)
	{
		m_VPMatrix = m_Camera.getProjectionMatrix() * newViewMatrixValue;
	}

	Renderer::Renderer(Camera& camera)
		: m_Camera(camera), m_VPMatrix(m_Camera.getProjectionMatrix() * m_Camera.getViewMatrix())
	{
		camera.transform.onViewMatrixChange += [&](const glm::mat4& newViewMatrixValue) { calculateVP(newViewMatrixValue); };
	}

	void Renderer::draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const
	{
		vertexArray.bind();
		indexBuffer.bind();
		shader.bind();
		E(glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr));
	}

	void Renderer::draw(Mesh* mesh)
	{
		mesh->vertexArray.bind();
		mesh->indexBuffer.bind();
		mesh->material.bind(m_BoundTransformPtr->getModelMatrix(), m_VPMatrix, 10, 11);
		E(glDrawElements(GL_TRIANGLES, mesh->indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr));
	}

	void Renderer::clear() const
	{
		E(glClearColor(0.5, 0.5, 0.5, 0.5));
		E(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}
}