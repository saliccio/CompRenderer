#pragma once
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "Shader.h"

namespace CompRenderer {
    class Model {
    private:
        std::vector<Mesh*> m_Meshes;
        std::string m_Directory;

        void processNode(aiNode* node, const aiScene* scene);
        Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture*> loadMaterialTextures(aiMaterial* mat, aiTextureType type);
        
        friend class RenderModel;
    public:
        void loadModel(const std::string& path);
        inline std::vector<Mesh*>& getMeshes() { return m_Meshes; }
    public:
        Model() {

        }

        Model(const std::string& path)
        {
            loadModel(path);
        }
    };
}