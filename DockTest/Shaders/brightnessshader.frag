#version 330 core
in vec2 TexCoords;

out vec4 outColor;

uniform sampler2D deferredTexture;


void main(void)
{
    vec4 sceneColour = texture2D(deferredTexture, TexCoords);
    float brightnessshader = (sceneColour.x*0.2126) + (sceneColour.y*0.7152)+ (sceneColour.z*0.0722);
    if(brightnessshader>0.7)
    {
        outColor = sceneColour;
    }
    else
    {
        outColor = vec4(0,0,0,1);
    }

}
