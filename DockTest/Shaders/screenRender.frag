#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Color;

uniform sampler2D screenTexture;

void main(void)
{      
    FragColor = texture2D(screenTexture, TexCoords);
    //FragColor = vec4(Color, 1.0);
}
