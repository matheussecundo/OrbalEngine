#include "camera.h"
#include "../utils/utils.h"

Camera *Camera::current = nullptr;

Camera::Camera() : UP(0.0f, 1.0f, 0.0f), ViewDirection(0.0f, 0.0f, -1.0f), Movement_Speed(0.3f) {
    Projection.setToIdentity();
}

Mat4 Camera::getWorldToViewMatrix() const{
    Mat4 result;
    result.lookAt(Position, Position + ViewDirection, UP);
    return result;
}

void Camera::rotate(float xAngle, float yAngle){
    Quaternion quater;
    quater = quater.fromEulerAngles(0, xAngle, 0);
    Mat4 rotate;
    rotate.rotate(quater);

    ViewDirection = rotate * ViewDirection;

    ViewDirection.setY(ViewDirection.y() + yAngle*0.02f); //gambiarra, refazer depois

    ViewDirection.normalize();
}

void Camera::moveFoward(){
    Position += Movement_Speed * ViewDirection;
}
void Camera::moveBackward(){
    Position += -Movement_Speed * ViewDirection;
}
void Camera::strafeLeft(){
    Vec3 strafeDirection = Vec3::crossProduct(ViewDirection, UP);
    Position += -Movement_Speed * strafeDirection;
}
void Camera::strafeRight(){
    Vec3 strafeDirection = Vec3::crossProduct(ViewDirection, UP);
    Position += Movement_Speed * strafeDirection;
}
