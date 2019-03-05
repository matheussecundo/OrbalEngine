#pragma once

#include "../maths/mat.h"
#include "../maths/quaternion.h"

class Camera{

public:
    static Camera *current;

    const vec3 UP;
    vec3 position;
    vec3 viewDirection;

    mat4 projection;

    float movement_speed;

public:
    Camera();

    mat4 worldToViewMatrix() const;

    void rotate(float xAngle, float yAngle);

    void moveFoward();
    void moveBackward();
    void strafeLeft();
    void strafeRight();
};
