#pragma once
#include <vector>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Vertex.h"
#include "Material.h"

namespace ComplementEngine {
    class Model;
    class Mesh {
    private:
        Model* m_ParentPtr;

        void setupMesh();
    public:
        VertexArray vertexArray;
        IndexBuffer indexBuffer;
        Material material;

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Material& material, Model* modelPtr);

        inline Model* getParent() const { return m_ParentPtr; }
    };
}