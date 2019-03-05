#pragma once

#include "../maths/mat.h"
#include "../maths/quaternion.h"

class Camera{

public:
    static Camera *current;

    const Vec3 UP;
    Vec3 Position;
    Vec3 ViewDirection;

    Mat4 Projection;

    float Movement_Speed;

public:
    Camera();

    Mat4 getWorldToViewMatrix() const;

    void rotate(float xAngle, float yAngle);

    void moveFoward();
    void moveBackward();
    void strafeLeft();
    void strafeRight();
};
