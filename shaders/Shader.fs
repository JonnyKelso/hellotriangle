#version 330 core
struct Material {
    sampler2D diffuse;
    //vec3 ambient;
    //vec3 diffuse;
    sampler2D specular;
    float shininess;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};
struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


out vec4 FragColor;

//in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;


// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 viewPos;
uniform Material material;
uniform SpotLight spotLight;
uniform DirLight dirLight;

#define NR_SPOT_LIGHTS 5
uniform SpotLight spotLights[NR_SPOT_LIGHTS];

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir);
void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 result;// = CalcSpotLight(spotLight, norm, viewDir);
    //result += CalcDirLight(dirLight, norm, viewDir);
    
    for(int i = 0; i < NR_SPOT_LIGHTS; i++)
        result += CalcSpotLight(spotLights[i], norm, viewDir);
    
    
    FragColor = vec4(result, 1.0);
    //vec4 sl = (spot, 1.0);
    //vec4 dl = (dirLight, 1.0);
    //FragColor += sl;
    //FragColor += dl;
    
}
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - FragPos);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    
    float diff = max(dot(normal, lightDir), 0.0);
    //vec3 diffuse = (diff * material.diffuse) * light.diffuse;
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
    
    // specular
    //vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
    
    //ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    // we'll leave ambient unaffected so we always have a little light.
    diffuse  *= intensity;
    specular *= intensity;

    vec3 result = (ambient + diffuse + specular);
        
    return result;
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
    return (ambient + diffuse + specular);
}
