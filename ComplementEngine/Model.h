#pragma once
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "Shader.h"

namespace ComplementEngine {
    class Model {
    private:
        // model data
        std::vector<Mesh*> m_Meshes;
        std::string m_Directory;

        void loadModel(const std::string& path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture*> loadMaterialTextures(aiMaterial* mat, aiTextureType type);
        
        inline std::vector<Mesh*>& getMeshes() { return m_Meshes; }
        friend class RenderModel;
    public:
        Model() {

        }

        Model(const std::string& path)
        {
            loadModel(path);
        }
    };
}