#ifndef CAMERA_H
#define CAMERA_H


#include "QVector4D"
#include "QVector3D"
#include "QVector2D"
class Camera
{
public:
    Camera();

    QVector4D GetLeftRightBottomTop();

    QVector3D ScreenPointToWorldRay(int x, int y);
    QVector3D ScreenDisplacementToWorldVector(int x0,int y0, int x1, int y1, const QVector3D &worldPoint);

    QVector2D WorldToSecrenPoint(const QVector3D &worldPoint);

    void PrepareMatrices();

    int ViewportWidth = 128;
    int ViewportHeight = 128;

    float fovY = DEFAULT_CAMERA_FOV_Y;
    float zNear = DEFAULT_CAMERA_Z_NEAR;
    float zFar = DEFAULT_CAMERA_Z_FAR;

    float yaw = 0.0f;
    float pitch = 0.0f;

};

#endif // CAMERA_H
