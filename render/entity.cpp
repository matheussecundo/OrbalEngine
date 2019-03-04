#include "entity.h"

#include "../utils/utils.h"

Entity::Entity(Mesh *mesh, ShaderProgram* shaderprogram, Texture* texture) : m_Mesh(mesh), m_ShaderProgram(shaderprogram), m_Texture(texture){
    initializeOpenGLFunctions();

    mesh->getVertexListwithElements(m_VertexList, m_Elements);

    transform.setToIdentity();
}

Entity::~Entity(){

}

void Entity::setPosition(const Vec3& position){
    float* data = transform.data();
    data[12] = position.x();
    data[13] = position.y();
    data[14] = position.z();
}
void Entity::setPosition(float x, float y, float z){
    float* data = transform.data();
    data[12] = x;
    data[13] = y;
    data[14] = z;
}
