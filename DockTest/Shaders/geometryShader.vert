#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texCoord;

uniform mat4 projectionMat;
uniform mat4 modelViewMat;
uniform mat4 modelMat;

out Data
{
    vec3 positionViewspace;
    vec3 normalWorldspace;
    vec2 texCoord;
    vec3 positionWorldspace;

}VSOut;

void main(void)
{
    VSOut.positionViewspace = (modelViewMat * vec4(position, 1)).xyz;
    VSOut.normalWorldspace = normal;
    VSOut.texCoord = texCoord;
    VSOut.positionWorldspace = (modelMat * vec4(position, 1)).xyz;

    gl_Position = projectionMat * vec4(VSOut.positionViewspace, 1.0);
}
