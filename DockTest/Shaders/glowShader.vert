#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aColor;

out vec2 TexCoords;
out vec3 Color;

void main(void)
{
    gl_Position = vec4(aPos, 1.0);
    TexCoords = aTexCoords;
    Color = aColor;
}