#include "camera.h"
#include "../utils/utils.h"

Camera *Camera::current = nullptr;

Camera::Camera() : UP(0.0f, 1.0f, 0.0f), viewDirection(0.0f, 0.0f, -1.0f), movement_speed(0.3f) {
    projection.setToIdentity();
}

Mat4 Camera::worldToViewMatrix() const{
    Mat4 result;
    result.lookAt(position, position + viewDirection, UP);
    return result;
}

void Camera::rotate(float xAngle, float yAngle){
    Quaternion quater;
    quater = quater.fromEulerAngles(0, xAngle, 0);
    Mat4 rotate;
    rotate.rotate(quater);

    viewDirection = rotate * viewDirection;

    viewDirection.setY(viewDirection.y() + yAngle*0.02f); //gambiarra, refazer depois

    viewDirection.normalize();
}

void Camera::moveFoward(){
    position += movement_speed * viewDirection;
}
void Camera::moveBackward(){
    position += -movement_speed * viewDirection;
}
void Camera::strafeLeft(){
    Vec3 strafeDirection = Vec3::crossProduct(viewDirection, UP);
    position += -movement_speed * strafeDirection;
}
void Camera::strafeRight(){
    Vec3 strafeDirection = Vec3::crossProduct(viewDirection, UP);
    position += movement_speed * strafeDirection;
}
