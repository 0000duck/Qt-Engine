#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Color;

struct Light
{
    vec3 Position;
    vec3 Color;

    float Linear;
    float Quadratic;
};

uniform sampler2D gAlbedo;
uniform sampler2D gNormal;
uniform sampler2D gPosition;

const int NR_LIGHTS = 10;
uniform Light lights[NR_LIGHTS];
uniform vec3 viewPos;

uniform int renderView;

void main(void)
{
    vec3 Diffuse = texture2D(gAlbedo, TexCoords).rgb;
    vec3 Normal = texture2D(gNormal, TexCoords).rgb;
    vec3 FragPos = texture2D(gPosition, TexCoords).rgb;

    float Specular = texture2D(gAlbedo, TexCoords).a;
    vec3 lighting  = Diffuse * 0.1; // hard-coded ambient component
    vec3 viewDir  = normalize(viewPos - FragPos); // hard-coded ambient component

    for(int i = 0;i<NR_LIGHTS;i++)
    {
        vec3 lightDir = normalize(lights[i].Position-FragPos);
        vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * lights[i].Color;

        vec3 halfwayDir = normalize(lightDir+viewDir);
        float spec = pow(max(dot(Normal,halfwayDir),0.0), 16.0);
        vec3 specular = lights[i].Color*spec*Specular;

        float distance = length(lights[i].Position - FragPos);
        float attenuation = 1.0 / (1,0 + lights[i].Linear * distance + lights[i].Quadratic * distance * distance);
        diffuse *= attenuation;
        specular *= attenuation;
        lighting += diffuse+specular;
    }

    if(renderView == 0)
    {
        FragColor = vec4(lighting, 1.0);
    }
    else if (renderView == 1)
    {
        FragColor = vec4(Diffuse, 1.0);
    }
    else if (renderView == 2)
    {
        FragColor = vec4(Normal, 1.0);
    }
    else if (renderView == 3)
    {
        FragColor = vec4(FragPos, 1.0);
    }
    else
    {
        FragColor = vec4(1.0, 0.0, 1.0, 1.0);
    }
}
