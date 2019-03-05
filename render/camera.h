#pragma once

#include "../maths/mat.h"
#include "../maths/quaternion.h"

class Camera{

public:
    static Camera *current;

    const Vec3 UP;
    Vec3 position;
    Vec3 viewDirection;

    Mat4 projection;

    float movement_speed;

public:
    Camera();

    Mat4 worldToViewMatrix() const;

    void rotate(float xAngle, float yAngle);

    void moveFoward();
    void moveBackward();
    void strafeLeft();
    void strafeRight();
};
