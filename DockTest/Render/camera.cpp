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
QVector4D Camera::GetLeftRightBottomTop()
{
return QVector4D();
}

QVector3D Camera::ScreenPointToWorldRay(int x, int y)
{

    return QVector3D();

}
QVector3D Camera::ScreenDisplacementToWorldVector(int x0,int y0, int x1, int y1, const QVector3D &worldPoint)
{
    return QVector3D();

}

QVector2D Camera::WorldToSecrenPoint(const QVector3D &worldPoint)
{
    return QVector2D();

}
void Camera::SetViewport(int width,int height)
{
    viewportWidth = width;
    viewportHeight = height;
}
void Camera::PrepareMatrices()
{
    worldMatrix.setToIdentity();

    worldMatrix.translate(position);
    worldMatrix.rotate(yaw,QVector3D(0.0,1.0,0.0));
    worldMatrix.rotate(pitch,QVector3D(1.0,0.0,0.0));

    viewMatrix = worldMatrix.inverted();

    projectionMatrix.setToIdentity();

    projectionMatrix.perspective(fovY,(float)viewportWidth/(float)viewportHeight,zNear,zFar);
}

