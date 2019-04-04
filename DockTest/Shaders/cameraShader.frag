#version 330 core

/*
in Data
{
    vec3 color;
} FSIn;
*/


in Data
{
    vec3 positionView;
    vec3 normalView;

}FSIn;

out vec4 outColor;

void main(void)
{

vec3 L = -normalize(FSIn.positionView);
vec3 N = normalize(FSIn.normalView);
vec3 albedo = vec3(1.0);
float kD = max(0.0,dot(L,N));
outColor.rgb = albedo*kD;
outColor.a = 1.0;
outColor.rgb =pow(outColor.rgb,vec3(1.0,2.4));


   // outColor = vec4(FSIn.color, 1.0);

}
