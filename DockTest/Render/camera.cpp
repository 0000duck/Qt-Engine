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

    //worldMatrix.lookAt(position,position+cameraFront,cameraUp);

   // viewMatrix.lookAt(position,QVector3D(0.0,0.0,0.0),QVector3D(0.0,1.0,0.0));

    printf("----------|\n");
    printf("%f ",viewMatrix.data()[0]);
    printf("%f ",viewMatrix.data()[1]);
    printf("%f ",viewMatrix.data()[2]);
    printf("%f \n",viewMatrix.data()[3]);
    printf("%f ",viewMatrix.data()[4]);
    printf("%f ",viewMatrix.data()[5]);
    printf("%f ",viewMatrix.data()[6]);
    printf("%f \n",viewMatrix.data()[7]);
    printf("%f ",viewMatrix.data()[8]);
    printf("%f ",viewMatrix.data()[9]);
    printf("%f ",viewMatrix.data()[10]);
    printf("%f \n",viewMatrix.data()[11]);
    printf("%f ",viewMatrix.data()[12]);
    printf("%f ",viewMatrix.data()[13]);
    printf("%f ",viewMatrix.data()[14]);
    printf("%f \n",viewMatrix.data()[15]);


    printf("----------|\n");

    viewMatrix = worldMatrix.inverted();

    printf("----------|\n");
    printf("%f ",viewMatrix.data()[0]);
    printf("%f ",viewMatrix.data()[1]);
    printf("%f ",viewMatrix.data()[2]);
    printf("%f \n",viewMatrix.data()[3]);
    printf("%f ",viewMatrix.data()[4]);
    printf("%f ",viewMatrix.data()[5]);
    printf("%f ",viewMatrix.data()[6]);
    printf("%f \n",viewMatrix.data()[7]);
    printf("%f ",viewMatrix.data()[8]);
    printf("%f ",viewMatrix.data()[9]);
    printf("%f ",viewMatrix.data()[10]);
    printf("%f \n",viewMatrix.data()[11]);
    printf("%f ",viewMatrix.data()[12]);
    printf("%f ",viewMatrix.data()[13]);
    printf("%f ",viewMatrix.data()[14]);
    printf("%f \n",viewMatrix.data()[15]);


    printf("----------|\n");
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
