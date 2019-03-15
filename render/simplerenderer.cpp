#include "simplerenderer.h"

SimpleRenderer::SimpleRenderer(){

}

SimpleRenderer::~SimpleRenderer(){

}

void SimpleRenderer::submit(Entity *entity){
    if(entity)
        m_Entities.push_back(entity);
}

void SimpleRenderer::submit(const std::list<Entity*> &entities){
    for(auto entity : entities){
        if(entity)
            m_Entities.push_back(entity);
    }
}

void SimpleRenderer::submit(const std::vector<Entity*> &entities){
    for(auto entity : entities){
        if(entity)
            m_Entities.push_back(entity);
    }
}

void SimpleRenderer::flush(){
    for(auto entity : m_Entities){
        Buffer &arrayBuf = entity->arrayBuf;
        Buffer &indexBuf = entity->indexBuf;
        ShaderProgram* shaderprogram = entity->m_ShaderProgram;

        arrayBuf.bind();

        shaderprogram->bind();

        shaderprogram->setUniformValue("u_Model", entity->transform);

        // Tell OpenGL programmable pipeline how to locate vertex position data
        int a_positionLocation = shaderprogram->attributeLocation("a_position");
        shaderprogram->enableAttributeArray(a_positionLocation);
        shaderprogram->setAttributeBuffer(a_positionLocation, GL_FLOAT, offsetof(Vertex, vertice), 3, sizeof(Vertex));

        int a_texcoordLocation = shaderprogram->attributeLocation("a_texcoord");
        shaderprogram->enableAttributeArray(a_texcoordLocation);
        shaderprogram->setAttributeBuffer(a_texcoordLocation, GL_FLOAT, offsetof(Vertex, uv), 2, sizeof(Vertex));

        int a_normalLocation = shaderprogram->attributeLocation("a_normal");
        shaderprogram->enableAttributeArray(a_normalLocation);
        shaderprogram->setAttributeBuffer(a_normalLocation, GL_FLOAT, offsetof(Vertex, normal), 3, sizeof(Vertex));

        if(entity->m_Texture){
            entity->m_Texture->bind();
            // Use texture unit 0 which contains stallTexture.png
            shaderprogram->setUniformValue("u_texture", 0);
        }

        // Draw geometry using indices from VBO 1
        if(indexBuf.isCreated()){
            indexBuf.bind();
            glDrawElements(GL_TRIANGLES, indexBuf.size()/sizeof(GLushort), GL_UNSIGNED_SHORT, nullptr);
            indexBuf.release();
        }else{
            glDrawArrays(GL_TRIANGLES, 0, arrayBuf.size()/sizeof(Vertex));
        }
        arrayBuf.release();

    }
	m_Entities.clear();
}
