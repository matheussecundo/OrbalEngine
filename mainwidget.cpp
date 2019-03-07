#include "mainwidget.h"

#include <QMouseEvent>

#include "utils/utils.h"

MainWidget::MainWidget(QWidget *parent)
    : QOpenGLWidget(parent) {

}

MainWidget::~MainWidget(){
    makeCurrent();
    doneCurrent();
}

void MainWidget::mouseMoveEvent(QMouseEvent *e) {
    vec2 newMousePosition = vec2(e->localPos());
    vec2 mouseDelta = newMousePosition - m_MousePressPosition;

    float xAngle = mouseDelta.x() * 180.0f/width();
    float yAngle = mouseDelta.y() * 90.0f/height();

    m_Camera.rotate(xAngle, yAngle);

    m_MousePressPosition = newMousePosition;
}

void MainWidget::mousePressEvent(QMouseEvent *e){
    m_MousePressPosition = vec2(e->localPos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e){

}

void MainWidget::keyPressEvent(QKeyEvent *e){
    //LOG << e->text();

    switch (e->key()) {
    case Qt::Key_W:     m_Camera.moveFoward(); break;
    case Qt::Key_S:     m_Camera.moveBackward(); break;
    case Qt::Key_A:     m_Camera.strafeLeft(); break;
    case Qt::Key_D:     m_Camera.strafeRight(); break;
    case Qt::Key_0:     m_Camera.position = {0,1,10}; m_Camera.viewDirection = {0,0,-1}; break;
    default:;
    }
}

void MainWidget::keyReleaseEvent(QKeyEvent *e){
    //LOG << e->text();
}

void MainWidget::timerEvent(QTimerEvent *e){

}

void MainWidget::initializeGL(){
    initializeOpenGLFunctions();
    LOG << (const char*)glGetString(GL_VERSION);

    glClearColor(0, 0, 0, 1);
    initShaders();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    Texture *texture_stall;
    // Load stallTexture.png image
    texture_stall = new Texture(Image(":textures/stallTexture.png").mirrored());
    // Set nearest filtering mode for texture minification
    texture_stall->setMinificationFilter(Texture::Nearest);
    // Set bilinear filtering mode for texture magnification
    texture_stall->setMagnificationFilter(Texture::Linear);
    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture_stall->setWrapMode(Texture::Repeat);

    Texture *texture_Plane;
    texture_Plane = new Texture(Image(":textures/Plane.png").mirrored());
    texture_Plane->setMinificationFilter(Texture::Nearest);
    texture_Plane->setMagnificationFilter(Texture::Linear);
    texture_Plane->setWrapMode(Texture::Repeat);

    //Load Entities
    entities.push_back(new Entity(new Mesh(":/models/piramide.obj"), &shaderprogram));
    entities.push_back(new Entity(new Mesh(":/models/cube.obj"), &shaderprogram));
    entities.push_back(new Entity(new Mesh(":/models/stall.obj"), &shaderprogram, texture_stall));
    entities.push_back(new Entity(new Mesh(":/models/Plane.obj"), &shaderprogram, texture_Plane));

    Camera::current = &m_Camera;

    Camera::current->position = {0,1,10};

    entities[0]->position = {0,1,0};
    entities[1]->position = {4,1,0};
    entities[2]->position = {-8,-1,0};
    entities[3]->position = {0,-1,0};
    entities[3]->transform.scale(2);

    //Light settings
    shaderprogram.setUniformValue("u_ambientLight_strength", 0.15f);
    shaderprogram.setUniformValue("u_specularLight_strength", 1.0f);
    shaderprogram.setUniformValue("u_viewPos", Camera::current->position);
    shaderprogram.setUniformValue("u_lightPos", vec3(0,6,0));
    shaderprogram.setUniformValue("u_lightColor", vec3(1,1,1));

    timer.start(12, this);
    m_Rendercount.start();
}

void MainWidget::initShaders(){
    // Compile vertex shader
    if (!shaderprogram.addShaderFromSourceFile(Shader::Vertex, ":/shaders/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!shaderprogram.addShaderFromSourceFile(Shader::Fragment, ":/shaders/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!shaderprogram.link())
        close();

    // Bind shader pipeline for use
    if (!shaderprogram.bind())
        close();
}

void MainWidget::resizeGL(int w, int h){
    float aspectRatio = float(w) / float(h ? h : 1);
    const float zNear = 1.0, zFar = 100.0, fov = 45.0;

    m_Camera.projection.setToIdentity();
    m_Camera.projection.perspective(fov, aspectRatio, zNear, zFar);
}

void MainWidget::paintGL(){
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set modelview-projection matrix -> Projection * View * Model
    shaderprogram.setUniformValue("u_Projection", Camera::current->projection);
    shaderprogram.setUniformValue("u_View", Camera::current->worldToViewMatrix());

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

        //transfer view position
        shaderprogram.setUniformValue("u_viewPos", Camera::current->position);

        //source Light move with the camera
        //shaderprogram.setUniformValue("u_lightPos", Camera::current->position);
    }

    if(m_Rendercount.timetoTick){
        m_Rendercount.timetoTick = false;
        setWindowTitle("Orbal Engine | FPS: " + QString::number(m_Rendercount.getFPS()) + ", UPS: " + QString::number(m_Rendercount.getUPS()));
    }

    // Request an update and swap buffers
    update();
}
