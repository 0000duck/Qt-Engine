#version 330 core

in Data
{
    vec3 positionViewspace;
    vec3 normalViewspace;
    vec2 texCoord;
}FSIn;

layout(location=0) out vec4 albedo;
layout(location=1) out vec4 normals;
layout(location=2) out vec4 position;

uniform sampler2D texture;

void main(void)
{
    albedo = texture2D(texture, FSIn.texCoord);
    normals = FSIn.normalViewspace * 0.5 + vec3(0.5);
    position= FSIn.positionViewspace;
}
