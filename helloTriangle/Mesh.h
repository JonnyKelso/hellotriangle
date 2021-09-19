//
//  Mesh.h
//  helloTriangle
//
//  Created by Jonny Kelso on 16/10/2020.
//  Copyright © 2020 Jonny Kelso. All rights reserved.
//

#pragma once

#include "Binder.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace Graphics
{
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
        glm::vec3 Tangent;
        glm::vec3 Bitangent;
    };
    struct Texture
    {
        unsigned int id;
        std::string type;
        std::filesystem::path file;
    };

    class Mesh
    {
        public:
            // mesh data
            Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
            
            Mesh(Mesh&&) noexcept = default;
            //Mesh& operator=(Mesh&&) noexcept = default;
        
            void Draw(ShaderProgram &shader);
        
        private:
            //  render data
            VAOBinder m_VAO;
            VBOBinder m_VBO;
            EBOBinder m_EBO;
        
            std::vector<Vertex>       m_Vertices;
            std::vector<unsigned int> m_Indices;
            std::vector<Texture>      m_Textures;
            void setupMesh();
    };
}
