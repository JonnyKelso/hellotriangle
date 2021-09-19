#include "Cubes.h"
#include "Shader.h"
#include "Binder.h"

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
