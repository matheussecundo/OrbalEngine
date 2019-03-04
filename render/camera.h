#pragma once

#include "../maths/mat.h"
#include "../maths/quaternion.h"

class Camera{

public:

    const Vec3 m_UP;
    Vec3 m_Position;
    Vec3 m_ViewDirection;

    Mat4 m_Projection;

    float m_Movement_Speed;

public:
    Camera();

    Mat4 getWorldToViewMatrix() const;

    void rotate(float xAngle, float yAngle);

    void moveFoward();
    void moveBackward();
    void strafeLeft();
    void strafeRight();
};
