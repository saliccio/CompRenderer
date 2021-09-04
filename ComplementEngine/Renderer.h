#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Camera.h"

namespace ComplementEngine {
	class Mesh;
	class Material;
	class Shader;

	class Renderer {
	private:
		Camera m_Camera;
		glm::mat4 m_VPMatrix;		// caching

		Transform* m_BoundTransformPtr;
		void calculateVP(const glm::mat4& newValue);
	public:
		Renderer(Camera& camera);

		inline void setBoundTransformPtr(Transform* transformPtr) { m_BoundTransformPtr = transformPtr; }

		void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;
		void draw(Mesh* mesh);
		void clear() const;
	};
}