
#pragma once

#include "Mesh.h"
//#include "Shader.h"
#include <assimp/Importer.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <filesystem>
#include "stb_image.h"

namespace Graphics
{
    class Model
    {
        public:
        Model(const std::filesystem::path& path, bool gamma = false)
        {
            loadModel(path.string());
        }
        Model(Model&&) noexcept = default;
        Model& operator=(Model&&) noexcept = default;
        
        void Draw(ShaderProgram &shader);
    private:
        // model data
        std::vector<Mesh> m_Meshes;
        std::filesystem::path m_Directory;
        std::vector<Texture> m_LoadedTextures;
    bool gammaCorrection;
    
        void loadModel(const std::filesystem::path& path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
        
    };
}
