#include "camera.h"

Camera::Camera()
{

}
//https://www.3dgep.com/understanding-the-view-matrix/
/*
mat4 LookAtRH( vec3 eye, vec3 target, vec3 up )
{
    vec3 zaxis = normal(eye - target);    // The "forward" vector.
    vec3 xaxis = normal(cross(up, zaxis));// The "right" vector.
    vec3 yaxis = cross(zaxis, xaxis);     // The "up" vector.

    // Create a 4x4 view matrix from the right, up, forward and eye position vectors
    mat4 viewMatrix = {
        vec4(      xaxis.x,            yaxis.x,            zaxis.x,       0 ),
        vec4(      xaxis.y,            yaxis.y,            zaxis.y,       0 ),
        vec4(      xaxis.z,            yaxis.z,            zaxis.z,       0 ),
        vec4(-dot( xaxis, eye ), -dot( yaxis, eye ), -dot( zaxis, eye ),  1 )
    };

    return viewMatrix;
}
*/
