#include "geometryengine.h"

#include "maths/vec.h"

struct VertexData{
    Vec3 position;
    Vec2 texCoord;
};

GeometryEngine::GeometryEngine() : arrayBuf(Buffer::VertexBuffer), indexBuf(Buffer::IndexBuffer){
    initializeOpenGLFunctions();

    arrayBuf.create();
    indexBuf.create();

    initCubeGeometry();
}

GeometryEngine::~GeometryEngine(){
    arrayBuf.destroy();
    indexBuf.destroy();
}

void GeometryEngine::initCubeGeometry(){
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    VertexData vertices[] = {
        // Vertex data for face 0
        {Vec3(-1.0f, -1.0f,  1.0f), Vec2(0.0f, 0.0f)},  // v0
        {Vec3( 1.0f, -1.0f,  1.0f), Vec2(0.33f, 0.0f)}, // v1
        {Vec3(-1.0f,  1.0f,  1.0f), Vec2(0.0f, 0.5f)},  // v2
        {Vec3( 1.0f,  1.0f,  1.0f), Vec2(0.33f, 0.5f)}, // v3

        // Vertex data for face 1
        {Vec3( 1.0f, -1.0f,  1.0f), Vec2( 0.0f, 0.5f)}, // v4
        {Vec3( 1.0f, -1.0f, -1.0f), Vec2(0.33f, 0.5f)}, // v5
        {Vec3( 1.0f,  1.0f,  1.0f), Vec2(0.0f, 1.0f)},  // v6
        {Vec3( 1.0f,  1.0f, -1.0f), Vec2(0.33f, 1.0f)}, // v7

        // Vertex data for face 2
        {Vec3( 1.0f, -1.0f, -1.0f), Vec2(0.66f, 0.5f)}, // v8
        {Vec3(-1.0f, -1.0f, -1.0f), Vec2(1.0f, 0.5f)},  // v9
        {Vec3( 1.0f,  1.0f, -1.0f), Vec2(0.66f, 1.0f)}, // v10
        {Vec3(-1.0f,  1.0f, -1.0f), Vec2(1.0f, 1.0f)},  // v11

        // Vertex data for face 3
        {Vec3(-1.0f, -1.0f, -1.0f), Vec2(0.66f, 0.0f)}, // v12
        {Vec3(-1.0f, -1.0f,  1.0f), Vec2(1.0f, 0.0f)},  // v13
        {Vec3(-1.0f,  1.0f, -1.0f), Vec2(0.66f, 0.5f)}, // v14
        {Vec3(-1.0f,  1.0f,  1.0f), Vec2(1.0f, 0.5f)},  // v15

        // Vertex data for face 4
        {Vec3(-1.0f, -1.0f, -1.0f), Vec2(0.33f, 0.0f)}, // v16
        {Vec3( 1.0f, -1.0f, -1.0f), Vec2(0.66f, 0.0f)}, // v17
        {Vec3(-1.0f, -1.0f,  1.0f), Vec2(0.33f, 0.5f)}, // v18
        {Vec3( 1.0f, -1.0f,  1.0f), Vec2(0.66f, 0.5f)}, // v19

        // Vertex data for face 5
        {Vec3(-1.0f,  1.0f,  1.0f), Vec2(0.33f, 0.5f)}, // v20
        {Vec3( 1.0f,  1.0f,  1.0f), Vec2(0.66f, 0.5f)}, // v21
        {Vec3(-1.0f,  1.0f, -1.0f), Vec2(0.33f, 1.0f)}, // v22
        {Vec3( 1.0f,  1.0f, -1.0f), Vec2(0.66f, 1.0f)}  // v23
    };

    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, 24 * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, 34 * sizeof(GLushort));
}

void GeometryEngine::drawCubeGeometry(ShaderProgram *program){
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offsetof(VertexData, position), 3, sizeof(VertexData));

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offsetof(VertexData, texCoord), 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, nullptr);
}
