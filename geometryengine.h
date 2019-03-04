#pragma once

#include "opengl/openglfunc.h"
#include "opengl/shaderprogram.h"
#include "opengl/buffer.h"

class GeometryEngine : protected OpenGLFunc{

    Buffer arrayBuf;
    Buffer indexBuf;

public:
    GeometryEngine();
    virtual ~GeometryEngine();

    void drawCubeGeometry(ShaderProgram *program);

private:
    void initCubeGeometry();

};


