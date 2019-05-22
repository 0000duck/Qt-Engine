#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Color;

uniform sampler2D gAlbedo;
uniform sampler2D gNormal;
uniform sampler2D gPosition;

void main(void)
{
    vec3 Diffuse = texture2D(gAlbedo,TexCoords).rgb;
    vec3 Normal = texture2D(gNormal, TexCoords).rgb;
    vec3 FragPos = texture2D(gPosition, TexCoords).rgb;

    FragColor = vec4(Diffuse, 1.0);
}
