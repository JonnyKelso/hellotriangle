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

namespace Graphics::Examples
{
    constexpr std::size_t cols{ 8 };
    constexpr std::size_t rows{ 36 };
    constexpr std::array<float, cols*rows> vertices
    {
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
       0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,

      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,

      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f, 0.0f,  0.0f,
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -1.0f, 0.0f,  0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f, 0.0f,  0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f, 0.0f,  0.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  -1.0f, 0.0f,  0.0f,
      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f, 0.0f,  0.0f,

       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f,  0.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f,  0.0f,
       0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f,  0.0f,
       0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f,  0.0f,
       0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 0.0f,  0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f,  0.0f,

      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
       0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,

      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 1.0f,  0.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 1.0f,  0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f,  0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f,  0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 1.0f,  0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 1.0f,  0.0f,
    };

    constexpr std::array<float, 12> combinedVertices
    {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f   // top left
    };

    class Cubes
    {

    public:
        Cubes(const std::filesystem::path path, const std::filesystem::path specPath="") : cubeTexture(GL_TEXTURE0, path), specTexture(GL_TEXTURE1, specPath)
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW); // VBO
            //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, cols * sizeof(float), (void*)0); // VAO
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, cols * sizeof(float), (void*) (3 * sizeof(float))); // VAO
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, cols * sizeof(float), (void*)(5 * sizeof(float))); // VAO
            glEnableVertexAttribArray(2);
        }

        void bind();
        void Draw(Graphics::ShaderProgram &shader);
        Graphics::TextureBinder cubeTexture;
        Graphics::TextureBinder specTexture;
        
    private:
        Graphics::VBOBinder vbo{};
        Graphics::VAOBinder vao{};
        //Graphics::EBOBinder ebo{};
    };
}

