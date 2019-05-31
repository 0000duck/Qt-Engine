#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Color;

uniform int postProcessing;

uniform sampler2D deferredTexture;
uniform sampler2D blurTexture;
uniform sampler2D glowTexture;

void main(void)
{      
    if(postProcessing == 0)
    {
        FragColor = texture2D(deferredTexture, TexCoords);
    }
    else if (postProcessing == 1)
    {
        FragColor = texture2D(blurTexture, TexCoords);
    }
    else if (postProcessing == 2)
    {
        FragColor = texture2D(glowTexture, TexCoords);
    }
    else
    {
        FragColor = vec4(1.0, 0.0, 1.0, 1.0);
    }
}
