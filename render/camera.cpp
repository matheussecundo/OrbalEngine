#include "camera.h"
#include "../utils/utils.h"

Camera::Camera() : m_UP(0.0f, 1.0f, 0.0f), m_ViewDirection(0.0f, 0.0f, -1.0f), m_Movement_Speed(0.3f) {
    m_Projection.setToIdentity();
}

Mat4 Camera::getWorldToViewMatrix() const{
    Mat4 result;
    result.lookAt(m_Position, m_Position + m_ViewDirection, m_UP);
    return result;
}

void Camera::rotate(float xAngle, float yAngle){
    Quaternion quater;
    quater = quater.fromEulerAngles(0, xAngle, 0);
    Mat4 rotate;
    rotate.rotate(quater);

    m_ViewDirection = rotate * m_ViewDirection;

    m_ViewDirection.setY(m_ViewDirection.y() + yAngle*0.02f); //gambiarra, refazer depois

    m_ViewDirection.normalize();
}

void Camera::moveFoward(){
    m_Position += m_Movement_Speed * m_ViewDirection;
}
void Camera::moveBackward(){
    m_Position += -m_Movement_Speed * m_ViewDirection;
}
void Camera::strafeLeft(){
    Vec3 strafeDirection = Vec3::crossProduct(m_ViewDirection, m_UP);
    m_Position += -m_Movement_Speed * strafeDirection;
}
void Camera::strafeRight(){
    Vec3 strafeDirection = Vec3::crossProduct(m_ViewDirection, m_UP);
    m_Position += m_Movement_Speed * strafeDirection;
}
