#pragma once

#include "opengl/openglfunc.h"
#include "opengl/shaderprogram.h"
#include "opengl/texture.h"
#include "opengl/buffer.h"

#include "maths/mat.h"
#include <vector>

#include "mesh.h"

class Entity : protected OpenGLFunc{

public:
    std::vector<Vertex> m_VertexList;
    std::vector<GLushort> m_Elements;

    Buffer arrayBuf;
    Buffer indexBuf;
	
    Mesh *m_Mesh;
    ShaderProgram *m_ShaderProgram;
    Texture *m_Texture;

    mat4 transform;
    vec3 &position;

public:
    Entity(Mesh *mesh, ShaderProgram *shaderprogram = nullptr, Texture *texture = nullptr);
    virtual ~Entity();

};


