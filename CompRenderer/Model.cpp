#include "Model.h"

namespace CompRenderer {
    void Model::loadModel(const std::string& path)
    {
        Assimp::Importer import;
        const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << "Error! File could not be loaded." << std::endl;
            return;
        }

        m_Directory = path.substr(0, path.find_last_of('/'));

        processNode(scene->mRootNode, scene);
    }

    void Model::processNode(aiNode* node, const aiScene* scene)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            Mesh* meshToAdd = processMesh(mesh, scene);
            m_Meshes.push_back(meshToAdd);
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }
    }

    Mesh* Model::processMesh(aiMesh* mesh, const aiScene* scene)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture*> textures;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;

            if (mesh->mVertices != NULL) {
                aiVector3D assimpVertexPositions = mesh->mVertices[i];

                vertex.Position.x = assimpVertexPositions.x;
                vertex.Position.y = assimpVertexPositions.y;
                vertex.Position.z = assimpVertexPositions.z;
            }

            if (mesh->mNormals != NULL) {
                aiVector3D assimpVertexNormals = mesh->mNormals[i];

                vertex.Normal.x = assimpVertexNormals.x;
                vertex.Normal.y = assimpVertexNormals.y;
                vertex.Normal.z = assimpVertexNormals.z;
            }

            if (mesh->mTextureCoords != NULL)
            {
                aiVector3D assimpTexCoords = mesh->mTextureCoords[0][i];

                vertex.TexCoords.x = assimpTexCoords.x;
                vertex.TexCoords.y = assimpTexCoords.y;
            }
            else
            {
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);
            }

            vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        MaterialProperties materialProperties;

        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            std::vector<Texture*> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE);
            unsigned int endOfDiffuses;
            for (endOfDiffuses = 0; endOfDiffuses < diffuseMaps.size(); endOfDiffuses++) {
                textures.push_back(diffuseMaps[endOfDiffuses]);
            }

            std::vector<Texture*> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR);
            for (unsigned int i = 0; i < specularMaps.size(); i++) {
                textures.push_back(specularMaps[i]);
            }

            unsigned int texturesSize = textures.size();
            if (texturesSize > 0) {
                if (texturesSize >= endOfDiffuses + 1U) {
                    materialProperties = MaterialProperties(textures[0], textures[endOfDiffuses]);
                }
                else {
                    materialProperties = MaterialProperties(textures[0]);
                }
            }

            aiColor4D ambientColor{ 1.0f,1.0f,1.0f,1.0f };
            aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambientColor);
            if (ambientColor.IsBlack()) {
                ambientColor = aiColor4D{ 1.0f,1.0f,1.0f,1.0f };
            }
            materialProperties.ambientColor = glm::vec3(ambientColor.r, ambientColor.g, ambientColor.b);

            aiColor4D diffuseColor{ 1.0f,1.0f,1.0f,1.0f };
            aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor);
            materialProperties.diffuseColor = glm::vec3(diffuseColor.r, diffuseColor.g, diffuseColor.b);

            aiColor4D specularColor{ 1.0f,1.0f,1.0f,1.0f };
            aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specularColor);
            materialProperties.specularColor = glm::vec3(specularColor.r, specularColor.g, specularColor.b);

            float shininess;
            aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess);
            materialProperties.shininess = shininess;

            float opacity;
            aiGetMaterialFloat(material, AI_MATKEY_OPACITY, &opacity);
            materialProperties.opacity = opacity;
        }

        Mesh* finalMesh = new Mesh(vertices, indices, Material(&Shader::getShader("PhongShader.shader"), materialProperties), this);

        return finalMesh;
    }

    std::vector<Texture*> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type)
    {
        // TODO: CHECK FOR NOT TAKING THE SAME TEXTURE TWICE
        std::vector<Texture*> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            const char* fileName = str.C_Str();
            std::string fullPath = m_Directory + std::string(fileName);
            Texture::addTexture(fullPath, type);
            textures.push_back(Texture::getTexture(fullPath));
        }

        return textures;
    }
}