#version 330 core
in vec2 TexCoords;

out vec4 outColor;

uniform sampler2D colourTexture;
uniform sampler2D highlightTexture;

uniform float glowIntensity;

void main(void)
{
    vec4 sceneColour = texture2D(colourTexture, TexCoords);
    vec4 highlightColour = texture2D(highlightTexture, TexCoords);

    outColor = sceneColour + highlightColour * glowIntensity;

}
