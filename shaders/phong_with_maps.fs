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
    //vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};


struct Light {
    vec4 directionality;
    
    // spot light only
    float innerCutOff;
    float outerCutOff;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};

uniform vec3 viewPos;
uniform Material material;
#define NUM_LIGHTS 1
uniform Light light[NUM_LIGHTS];


void main()
{
    vec3 ambient, diffuse, specular;
    
    for(int i = 0; i < NUM_LIGHTS; i++)
    {
        
        // Ambient
        vec3 localAmbient = vec3(texture(material.diffuse, TexCoords)) * light[i].ambient;
        
        // Diffuse
        vec3 norm = normalize(Normal);
        float w = light[i].directionality.w;   // 0 is directional, 1 is point
        vec3 rawLightDir = light[i].directionality.xyz * (2 * w - 1) - FragPos * w;
        vec3 lightDir = normalize(rawLightDir);
        
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 localDiffuse = vec3(texture(material.diffuse, TexCoords)) * light[i].diffuse * diff;
        
        // Specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 localSpecular = spec * vec3(texture(material.specular, TexCoords)) * light[i].specular;
        
        float distance    = length(rawLightDir);
        float attenuation = pow(1.0 / (light[i].constant + light[i].linear * distance + light[i].quadratic * (distance * distance)), w);
        
        if(w!=0)
        {
            float cosTheta = dot(lightDir, normalize(light[i].directionality.xyz));
            float epsilon   = light[i].innerCutOff - light[i].outerCutOff;
            float intensity = (epsilon != 0) ? clamp((cosTheta - light[i].outerCutOff) / epsilon, 0.0, 1.0) : 1.0;
            
            localDiffuse *= intensity;
            localSpecular *= intensity;
        }
        localAmbient *= attenuation;
        localDiffuse *= attenuation;
        localSpecular *= attenuation;
        
        ambient += localAmbient;
        diffuse += localDiffuse;
        specular += localSpecular;
    }
    
    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
