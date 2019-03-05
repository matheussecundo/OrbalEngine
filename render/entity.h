#pragma once

#include "opengl/openglfunc.h"
#include "opengl/shaderprogram.h"
#include "opengl/texture.h"

#include "maths/mat.h"
#include <vector>

#include "mesh.h"

class Entity : protected OpenGLFunc{

public:
    std::vector<Vertex> m_VertexList;
    std::vector<GLushort> m_Elements;
	
    Mesh *m_Mesh;
    ShaderProgram *m_ShaderProgram;
    Texture *m_Texture;

    Mat4 transform;

public:
    Entity(Mesh *mesh, ShaderProgram *shaderprogram = nullptr, Texture *texture = nullptr);
    virtual ~Entity();

    void setPosition(const Vec3& position);
    void setPosition(float x, float y, float z);

};


