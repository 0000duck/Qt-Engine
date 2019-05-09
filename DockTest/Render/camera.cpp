#include "camera.h"
#include "QtMath"

Camera::Camera()
{
 UpdateCameraVectors();
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
float aspectRatio = float(viewportWidth)/float(viewportHeight);
float alpha = qDegreesToRadians(fovY*0.5);
float top = zNear*qTan(alpha);
float bottom = -top;
float right = top*aspectRatio;
float left = -right;

return QVector4D(left,right,bottom,top);
}

QVector3D Camera::ScreenPointToWorldRay(int x, int y)
{
    QVector4D lrbt = GetLeftRightBottomTop();
    float rayX = lrbt.x()*(lrbt.y()-lrbt.x()) * x/viewportWidth;
    float rayY = lrbt.z()*(lrbt.w()-lrbt.z()) * (viewportHeight-y-1)/viewportHeight;
    float rayZ = -zNear;

    QVector3D rayViewspace = QVector3D(rayX,rayY,rayZ);

    PrepareMatrices();
    QVector3D rayWorldspace = QVector3D(worldMatrix*QVector4D(rayViewspace,0.0f));

    return rayWorldspace;

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
void Camera::LookAt(const QVector3D &target)
{
    QVector3D direction = (position-target).normalized();

    float r = qSqrt( direction.x()*direction.x() + direction.z()*direction.z());

    pitch = -qRadiansToDegrees(qAtan2(direction.y(),r));
    yaw = qRadiansToDegrees(qAtan2(direction.x(),direction.z()));
}
void Camera::PrepareMatrices()
{
    worldMatrix.setToIdentity();

    worldMatrix.translate(position);
    worldMatrix.rotate(yaw,QVector3D(0,1,0));
    worldMatrix.rotate(pitch,QVector3D(1,0,0));

    viewMatrix = worldMatrix.inverted();


    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(fovY,(float)viewportWidth/(float)viewportHeight,zNear,zFar);
}

void Camera::ProcessKeyboard(CameraMovement direction,float deltaTime)
{

    float velocity =  speed * deltaTime;

    if (direction == CameraMovement::FORWARD)
        position += cameraFront * velocity;
    if (direction == CameraMovement::BACKWARD)
        position -= cameraFront * velocity;
    if (direction == CameraMovement::LEFT)
        position -= cameraRight * velocity;
    if (direction == CameraMovement::RIGHT)
        position += cameraRight * velocity;

}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
   {

       xoffset *= 0.3;
       yoffset *= 0.3;

       yaw   += xoffset;
       pitch += yoffset;

       // Make sure that when pitch is out of bounds, screen doesn't get flipped
       if (constrainPitch)
       {
           if (pitch > 89.0f)
               pitch = 89.0f;
           if (pitch < -89.0f)
               pitch = -89.0f;
       }


       // Update Front, Right and Up Vectors using the updated Euler angles
       UpdateCameraVectors();
   }
void Camera::ProcessScrollMovement(float yoffset)
   {
    if (fovY >= 20.0f && fovY <= 145.0f)
             fovY -= yoffset;
         if (fovY <= 20.0f)
             fovY = 20.0f;
         if (fovY >= 145.0f)
             fovY = 145.0f;

         printf("fovY %i\n",fovY);

   }
void Camera::UpdateCameraVectors()
{
    QVector3D front;

    front.setX(-sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
    front.setY(sinf(qDegreesToRadians(pitch)));
    front.setZ(-cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));

    cameraFront = front.normalized();


    cameraRight = QVector3D::crossProduct(cameraFront,QVector3D(0,1,0)).normalized();
    cameraUp = QVector3D::crossProduct(cameraRight,cameraFront).normalized();

}



/*
 *

 glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // Also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up    = glm::normalize(glm::cross(Right, Front));*/
