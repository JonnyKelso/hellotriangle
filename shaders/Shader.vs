#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

//out vec3 ourColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    //gl_Position = vec4(aPos, 1.0);
    
    //gl_Position = transform * vec4(aPos, 1.0f);
    // note that we read the multiplication from right to left
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    //ourColor = vec3(0.5,0.5,0.1); //aColor;
    TexCoord = aTexCoord; //vec2(aTexCoord.x, aTexCoord.y);

    Normal = mat3(transpose(inverse(model))) * aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));
}
