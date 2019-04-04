#version 330 core

layout(location=0) in vec3 position;
//layout(location=1) in vec3 color;

layout(location=1) in vec3 normal;

/*
out Data
{
    vec3 color;
}VSOut;

*/


out Data
{
    vec3 positionView;
    vec3 normalView;

}VSOut;



uniform mat4 MVP;



void main(void)
{
    /*
    MVP*vec4(position,1.0);
    VSOut.positionView = MVP*vec4(position,1.0);
    VSOut.normalView = MVP*vec4(normal,1.0);

    */
   // VSOut.color = color;

    gl_Position = MVP*vec4(position,1.0);
}
