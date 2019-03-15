#include "entity.h"

#include "../utils/utils.h"

Entity::Entity(Mesh *mesh, ShaderProgram *shaderprogram, Texture *texture)
    : arrayBuf(Buffer::VertexBuffer), indexBuf(Buffer::IndexBuffer), m_Mesh(mesh), m_ShaderProgram(shaderprogram), m_Texture(texture), position(*(vec3*)&transform.data()[12]){
    initializeOpenGLFunctions();

    std::vector<Vertex> vertexList;
    std::vector<GLushort> elements;
    mesh->getVertexList(vertexList);
    //mesh->getVertexListwithElements(m_VertexList, m_Elements); //Incomplete function

    arrayBuf.create();
    arrayBuf.bind();
    arrayBuf.allocate(&vertexList[0], vertexList.size() * sizeof(Vertex));
    if(elements.size()){
        indexBuf.create();
        indexBuf.bind();
        indexBuf.allocate(&elements[0], elements.size() * sizeof(GLushort));
        indexBuf.release();
    }
    arrayBuf.release();

    transform.setToIdentity();
}

Entity::~Entity(){
    arrayBuf.destroy();
    indexBuf.destroy();
}

