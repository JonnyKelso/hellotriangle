#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

struct Material {
    bool textured;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    sampler2D diffuseSampler;
    sampler2D specularSampler;
    float shininess;
};

struct Light {
    vec4 directionality;

    // For spotlights, only
    float innerCutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
#define MAX_NUM_LIGHTS 8
uniform Light light[MAX_NUM_LIGHTS];
uniform int numLights = 0;
uniform vec3 viewPos;
uniform float alphaThreshold = 0.0f;

void main()
{
    vec3 ambient, diffuse, specular;
    

    vec4 matAmbient  = material.textured ? texture(material.diffuseSampler, TexCoords) : vec4(material.ambient, 1.0f);
    vec3 mattDiffuse = material.textured ? vec3(texture(material.diffuseSampler, TexCoords)) : material.diffuse;
    vec3 matSpecular = material.textured ? vec3(texture(material.specularSampler, TexCoords)) : material.specular;
    
    
    for(int i=0; i<numLights; ++i)
    {
        // Ambient
        
        vec3 localAmbient = matAmbient.xyz * light[i].ambient;

        // Diffuse
        vec3 norm = normalize(Normal);
        float w = light[i].directionality.w;
        vec3 rawLightDir = light[i].directionality.xyz*(2*w-1) - FragPos*w;
        vec3 lightDir = normalize(rawLightDir);

        float diff = max(dot(norm, lightDir), 0.0);
        
        vec3 localDiffuse = diff * mattDiffuse * light[i].diffuse;

        // Specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);

        float dotProd = dot(viewDir, reflectDir);
        float spec = dotProd >  0 ? pow(max(dotProd, 0.0), material.shininess) : 1.0;
        
        vec3 localSpecular = spec * matSpecular * light[i].specular;

        // Attenuation
        float distance    = length(rawLightDir);
        float attenuation = pow(1.0 / (light[i].constant + light[i].linear * distance + light[i].quadratic * (distance * distance)), w);

        if(w != 0)
        {
          float cosTheta = dot(lightDir, normalize(light[i].directionality.xyz));

          float epsilon   = light[i].innerCutOff - light[i].outerCutOff;
          float intensity = (epsilon != 0) ? clamp((cosTheta - light[i].outerCutOff) / epsilon, 0.0, 1.0) :
                            (cosTheta > light[i].outerCutOff) ? 1.0 : 0.0;
          localDiffuse  *= intensity;
          localSpecular *= intensity;
        }

        localAmbient*=attenuation;
        localDiffuse*=attenuation;
        localSpecular*=attenuation;

        ambient += localAmbient;
        diffuse += localDiffuse;
        specular += localSpecular;
    }

    if(matAmbient.a < alphaThreshold)
            discard;
    
    FragColor = vec4(ambient + diffuse + specular, matAmbient.w);
}
