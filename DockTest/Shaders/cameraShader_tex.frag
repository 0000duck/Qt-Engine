#version 330 core

in Data
{
    vec3 positionViewspace;
    vec3 normalViewspace;
    vec2 texCoord;
}FSIn;

out vec4 outColor;

uniform sampler2D texture;

void main(void)
{
    outColor = texture2D(texture, FSIn.texCoord)
}
