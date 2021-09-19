#include "stbImageLoader.h"

#include <iostream>
#include <string>
#include <string_view>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VAOBinder
{
public:
    VAOBinder()
    {
        glGenVertexArrays(1, &m_VAO);
        //glBindBuffer(GL_ARRAY_BUFFER, &m_VAO);
    }
    
    VAOBinder(VAOBinder&& other) noexcept
    : m_VAO{ other.get() }
    {
        other.m_VAO = 0;
    }
    ~VAOBinder()
    {
        //glDeleteVertexArrays(1, &m_VAO);
    }
    unsigned int get() const
    {
        return m_VAO;
    }
    void bind() const
    {
      glBindVertexArray(m_VAO);
    }
private:
    GLuint m_VAO;

};

class VBOBinder
{
public:
    VBOBinder()
    {
        glGenBuffers(1, &m_VBO);
    }
    
    VBOBinder(const VBOBinder&) = delete;
    
    VBOBinder(VBOBinder&& other) noexcept
    : m_VBO{ other.get() }
    {
        other.m_VBO = 0;
    }
    
    VBOBinder& operator=(const VBOBinder& other) = delete;
    
    ~VBOBinder()
    {
        //glDeleteBuffers(1, &m_VBO);
    }
    
    unsigned int get() const
    {
        return m_VBO;
    }
    
    void bind() const
    {
      glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    }
private:
    GLuint m_VBO;

};

class EBOBinder
{
public:
    EBOBinder()
    {
        glGenBuffers(1, &m_EBO);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    }
    
    EBOBinder(EBOBinder&& other) noexcept
    : m_EBO{ other.get() }
    {
        other.m_EBO = 0;
    }
    
    ~EBOBinder()
    {
        //glDeleteBuffers(1, &m_EBO);
    }
    
    unsigned int get() const
    {
        return m_EBO;
    }
    void bind() const
    {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    }
private:
    GLuint m_EBO;

};

class TextureBinder
 {
public:
    TextureBinder(std::string fileName)
    {
        // texture
        glGenTextures(1, &m_Texture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_Texture);
        
        //stbi_set_flip_vertically_on_load(false);
        int width, height, nrComponents;
        stbImageLoader stbl;
        unsigned char *data = stbl.LoadImage(fileName.c_str(), width, height, nrComponents);
        if (data)
        {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else /*(nrComponents == 4)*/
                format = GL_RGBA;
            
            std::cout << "Loaded image data" << std::endl;
            Image2D(width, height, data, format);
            std::cout << "Loaded texture" << std::endl;
            
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbl.FreeImage(data);

    }
     
     TextureBinder(TextureBinder&& other)
     : m_Texture(other.get())
     {
         other.m_Texture = 0;
     }
     
     
    ~TextureBinder()
    {
        glDeleteVertexArrays(1, &m_Texture);
    }
    void Image2D(int width, int height, unsigned char* data, int RGBtype)
    {
        
        glTexImage2D(GL_TEXTURE_2D, 0, RGBtype, width, height, 0, RGBtype, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
    }
    void setTexture(std::string_view name, int index)
    {
        glUniform1i(glGetUniformLocation(m_Texture, name.data()), index);
    }

     GLuint get()
     {
         return m_Texture;
     }
 private:
     GLuint m_Texture{};
     int m_gl_texture{};
};
