//
//  Cubes.cpp
//  helloTriangle
//
//  Created by Jonny Kelso on 07/01/2021.
//

#include "Cubes.h"
#include "Shader.h"
#include "Binder.h"


//Cubes::Cubes()
//{
//
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW); // VBO
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, cols * sizeof(float), (void*)0); // VAO
//    glEnableVertexAttribArray(0);
//
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, cols * sizeof(float), (void*) (3 * sizeof(float))); // VAO
//    glEnableVertexAttribArray(1);
//
//    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, cols * sizeof(float), (void*)(5 * sizeof(float))); // VAO
//    glEnableVertexAttribArray(2);
//    
//}
namespace Graphics::Examples
{
    void Cubes::bind()
    {
        vao.bind();
        vbo.bind();
        //ebo.bind();
        cubeTexture.bind();
        specTexture.bind();
    }

    void Cubes::Draw(Graphics::ShaderProgram &)
    {
        bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
