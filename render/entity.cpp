#include "entity.h"

#include "../utils/utils.h"

Entity::Entity(Mesh *mesh, ShaderProgram* shaderprogram, Texture* texture)
    : m_Mesh(mesh), m_ShaderProgram(shaderprogram), m_Texture(texture), position(*(Vec3*)&transform.data()[12]){

    initializeOpenGLFunctions();

    //mesh->getVertexListwithElements(m_VertexList, m_Elements); //Incomplete function
    mesh->getVertexList(m_VertexList);

    transform.setToIdentity();
}

Entity::~Entity(){

}

