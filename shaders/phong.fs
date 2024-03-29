#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

//uniform vec3 lightColor;
//uniform float ambientStrength;
//uniform float specularStrength;
//uniform float shininess;
//uniform vec3 lightPos;


struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};


struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPos;
uniform Material material;
uniform Light light;


void main()
{
    // Ambient
    vec3 ambient = material.ambient * light.ambient;
    
    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = material.diffuse * light.diffuse * diff;
    
    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);
    
    
    FragColor = vec4(ambient + diffuse + specular, 1.0f);
}
