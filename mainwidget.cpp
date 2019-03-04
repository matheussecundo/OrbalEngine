#include "mainwidget.h"

#include <QMouseEvent>

#include <math.h>

#include "utils/utils.h"

MainWidget::MainWidget(QWidget *parent)
    : QOpenGLWidget(parent), geometries(nullptr), texture(nullptr) {}

MainWidget::~MainWidget(){
    makeCurrent();
    delete texture;
    delete geometries;
    doneCurrent();
}

void MainWidget::mouseMoveEvent(QMouseEvent *e) {
    Vec2 newMousePosition = Vec2(e->localPos());
    Vec2 mouseDelta = newMousePosition - m_MousePressPosition;

    float xAngle = mouseDelta.x() * 180.0f/width();
    float yAngle = mouseDelta.y() * 90.0f/height();

    m_Camera.rotate(xAngle, yAngle);

    m_MousePressPosition = newMousePosition;
}

void MainWidget::mousePressEvent(QMouseEvent *e){
    m_MousePressPosition = Vec2(e->localPos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e){

}

void MainWidget::keyPressEvent(QKeyEvent *e){
    //LOG(e->text());
    switch (e->key()) {
    case Qt::Key_W:     m_Camera.moveFoward(); break;
    case Qt::Key_S:     m_Camera.moveBackward(); break;
    case Qt::Key_A:     m_Camera.strafeLeft(); break;
    case Qt::Key_D:     m_Camera.strafeRight(); break;
    case Qt::Key_0:     m_Camera.m_Position = {0,0,5}; m_Camera.m_ViewDirection = {0,0,-1}; break;
    default:;
    }

}

void MainWidget::timerEvent(QTimerEvent *e){

}

void MainWidget::initializeGL(){
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    //initTextures();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    LOG((const char*)glGetString(GL_VERSION));

    geometries = new GeometryEngine;

    entities.push_back(new Entity(new Mesh(":/models/piramide.obj"), &program));
    entities.push_back(new Entity(new Mesh(":/models/cube.obj"), &program));
    entities.push_back(new Entity(new Mesh(":/models/stall.obj"), &program));

    timer.start(12, this);
    m_Rendercount.start();

    m_Camera.m_Position = {0,0,5};

    entities[0]->setPosition(0,1,0);
    entities[1]->setPosition(4,1,0);
    entities[2]->setPosition(-8,1,0);

}

void MainWidget::initShaders(){
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(Shader::Vertex, ":/shaders/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(Shader::Fragment, ":/shaders/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}

void MainWidget::initTextures(){
    // Load cube.png image
    texture = new Texture(Image(":textures/cube.png").mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(Texture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(Texture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(Texture::Repeat);
}

void MainWidget::resizeGL(int w, int h){
    float aspectRatio = float(w) / float(h ? h : 1);
    const float zNear = 2.0, zFar = 50.0, fov = 45.0;

    m_Camera.m_Projection.setToIdentity();
    m_Camera.m_Projection.perspective(fov, aspectRatio, zNear, zFar);
}

void MainWidget::paintGL(){
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //texture->bind();

    // Set modelview-projection matrix -> Projection * View * Model
    program.setUniformValue("mvp_matrix", m_Camera.m_Projection * m_Camera.getWorldToViewMatrix());

    // Use texture unit 0 which contains cube.png
    //program.setUniformValue("texture", 0);

    // Draw cube geometry
    //geometries->drawCubeGeometry(&program);
	
    for(auto entity : entities)
        m_Renderer.submit(entity);

    m_Renderer.flush();
	
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(2,0,0);

        glVertex3f(0,0,0);
        glVertex3f(0,4,0);

        glVertex3f(0,0,0);
        glVertex3f(0,0,3);
    glEnd();

    m_Rendercount.count();

    if(m_Rendercount.timetoUpdate){
        m_Rendercount.timetoUpdate = false;
        entities[0]->transform.rotate(1,{0,1,0});
        //entity->transform.translate({0,0,0.01f});
    }

    if(m_Rendercount.timetoTick){
        m_Rendercount.timetoTick = false;
        setWindowTitle("Orbal Engine | FPS: " + QString::number(m_Rendercount.getFPS()) + ", UPS: " + QString::number(m_Rendercount.getUPS()));
    }

    // Request an update and swap buffers
    update();
}
