#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform vec2 texCoordsInc;
uniform sampler2D colorMap;

void main(void)
{
    float weights[11];

    weights[0] = 0.035822;
    weights[1] = 0.05879;
    weights[2] = 0.086425;
    weights[3] = 0.113806;
    weights[4] = 0.13424;
    weights[5] = 0.141836;
    weights[6] = 0.13424;
    weights[7] = 0.113806;
    weights[8] = 0.086425;
    weights[9] = 0.05879;
    weights[10] = 0.035822;

    vec3 blurredColor = vec3(0.0);

    vec2 uv = TexCoords-texCoordsInc*5.0;
    float sumWeights = 0.0f;

    for(int i = 0;i<11;++i)
    {
        blurredColor += texture2D(colorMap,uv).rgb*weights[i];
        sumWeights+=weights[i];
        uv+= texCoordsInc;
    }
    blurredColor /= sumWeights;
    FragColor = vec4(blurredColor,1.0);
}
