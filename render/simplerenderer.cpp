#include "simplerenderer.h"

SimpleRenderer::SimpleRenderer() : arrayBuf(Buffer::VertexBuffer), indexBuf(Buffer::IndexBuffer){

}

SimpleRenderer::~SimpleRenderer(){

}

void SimpleRenderer::submit(const Entity *entity){
    if(entity)
        m_Entities.push_back(entity);
}

void SimpleRenderer::flush(){
    for(auto entity : m_Entities){
        std::vector<Vertex> vertexList = entity->m_VertexList;
        const std::vector<GLushort> &elements = entity->m_Elements;
        ShaderProgram* shaderprogram = entity->m_ShaderProgram;
		
        for(Vertex& vertex : vertexList){
            vertex.vertice = entity->transform * vertex.vertice;
            vertex.normal = entity->transform * vertex.normal;
        }

        arrayBuf.create();
        arrayBuf.bind();
        arrayBuf.allocate(&vertexList[0], vertexList.size() * sizeof(Vertex));

        shaderprogram->bind();

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

        // Draw geometry using indices from VBO 1
        if(elements.size()){
            indexBuf.create();
            indexBuf.bind();
            indexBuf.allocate(&elements[0], elements.size() * sizeof(GLushort));
            glDrawElements(GL_TRIANGLES, elements.size(), GL_UNSIGNED_SHORT, nullptr);
            indexBuf.release();
            indexBuf.destroy();
        }else{
            glDrawArrays(GL_TRIANGLES, 0, vertexList.size());
        }

        arrayBuf.release();
        arrayBuf.destroy();

    }
	m_Entities.clear();
}
