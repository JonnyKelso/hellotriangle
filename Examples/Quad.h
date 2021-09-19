#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <filesystem>
#include <stdio.h>
#include <array>
#include "Binder.h"
#include "../helloTriangle/Shader.h"


namespace Graphics
{
    class ShaderProgram;
}

namespace Graphics::Examples
{

    class Quad
    {

    public:
            //Quad(const std::filesystem::path texPath, const std::filesystem::path specMapPath="");
            Quad(const std::filesystem::path texPath, const std::filesystem::path specMapPath="")
            : texture{GL_TEXTURE0, texPath}
            , specTexture{GL_TEXTURE1, specMapPath}
          {
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW); // VBO
            //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, cols * sizeof(float), (void*)0); // VAO
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, cols * sizeof(float), (void*)(3 * sizeof(float))); // VAO
            glEnableVertexAttribArray(1);
          }
        
        void bind();
        //void Draw(Graphics::ShaderProgram&);
        void Draw(Graphics::ShaderProgram&)
        {
          vbo.bind();
          vao.bind();
          //ebo.bind();
          texture.bind();
          specTexture.bind();

          glDrawArrays(GL_TRIANGLES, 0, 6);
        }
        
        
    private:
        Graphics::VBOBinder vbo{};
        Graphics::VAOBinder vao{};
        //Graphics::EBOBinder ebo{};
        Graphics::TextureBinder texture, specTexture;
        
        constexpr static std::size_t cols{ 5 };
        constexpr static std::size_t rows{ 6 };
        
        constexpr static std::array<float, cols* rows> vertices{
                  // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
                  0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
                  0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
                  1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

                  0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
                  1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
                  1.0f,  0.5f,  0.0f,  1.0f,  0.0f
                };
    };
}
