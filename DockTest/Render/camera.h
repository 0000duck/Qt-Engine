#ifndef CAMERA_H
#define CAMERA_H

#define DEFAULT_CAMERA_FOV_Y 70.0f
#define DEFAULT_CAMERA_Z_NEAR 1.0f
#define DEFAULT_CAMERA_Z_FAR 1000.0f
#define DEFAULT_CAMERA_SPEED 10.0f

#include "QVector4D"
#include "QVector3D"
#include "QVector2D"
#include "QMatrix4x4"
class Camera
{
public:
    Camera();

    QVector4D GetLeftRightBottomTop();

    QVector3D ScreenPointToWorldRay(int x, int y);
    QVector3D ScreenDisplacementToWorldVector(int x0,int y0, int x1, int y1, const QVector3D &worldPoint);

    QVector2D WorldToSecrenPoint(const QVector3D &worldPoint);

    void SetViewport(int width, int height);
    void PrepareMatrices();
public:


    int viewportWidth = 128;
    int viewportHeight = 128;

    float fovY = DEFAULT_CAMERA_FOV_Y;
    float zNear = DEFAULT_CAMERA_Z_NEAR;
    float zFar = DEFAULT_CAMERA_Z_FAR;

    float yaw = 0.0f;
    float pitch = 0.0f;

    QVector3D position;

    float speed = DEFAULT_CAMERA_SPEED;

    QMatrix4x4 worldMatrix;
    QMatrix4x4 viewMatrix;
    QMatrix4x4 projectionMatrix;

};

#endif // CAMERA_H
