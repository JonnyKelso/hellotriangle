
#include "Quad.h"

#include "../BinderOR.h"
#include "../Shader.h"

namespace Graphics::Examples
{
    

  void Quad::Draw(Graphics::ShaderProgram&)
  {
    vbo.bind();
    vao.bind();
    //ebo.bind();
    texture.bind();
    specTexture.bind();

    glDrawArrays(GL_TRIANGLES, 0, 6);
  }
}
