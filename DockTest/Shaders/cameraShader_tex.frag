#version 330 core

layout(location=0) out vec4 albedo;
layout(location=1) out vec3 normals;
layout(location=2) out vec3 position;

in Data
{
    vec3 positionViewspace;
    vec3 normalWorldspace;
    vec2 texCoord;
}FSIn;


uniform sampler2D texture;

void main(void)
{
    albedo = texture2D(texture, FSIn.texCoord);
    normals = normalize(FSIn.normalWorldspace);
    position = FSIn.positionViewspace;
}
