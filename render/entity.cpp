#include "entity.h"

#include "../utils/utils.h"

Entity::Entity(Mesh *mesh, ShaderProgram *shaderprogram, Texture *texture)
    : m_Mesh(mesh), m_ShaderProgram(shaderprogram), m_Texture(texture), position(*(vec3*)&transform.data()[12]){

    initializeOpenGLFunctions();

    //mesh->getVertexListwithElements(m_VertexList, m_Elements); //Incomplete function
    mesh->getVertexList(m_VertexList);

    arrayBuf.create();
    arrayBuf.bind();
    arrayBuf.allocate(&m_VertexList[0], m_VertexList.size() * sizeof(Vertex));
    if(m_Elements.size()){
        indexBuf.create();
        indexBuf.bind();
        indexBuf.allocate(&m_Elements[0], m_Elements.size() * sizeof(GLushort));
        indexBuf.release();
    }
    arrayBuf.release();

    transform.setToIdentity();
}

Entity::~Entity(){
    arrayBuf.destroy();
    indexBuf.destroy();
}

