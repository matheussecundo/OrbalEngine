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

double d_normal() {
    const double pi = 3.14159265359;
    const double nums = 1;
    double u = 0, v = 0, x = 0;

    srand(rand() + (int) time(NULL));

    for(unsigned int i = 0; i < nums; i++){
        u = rand() / (((double)RAND_MAX) + 1.0);
        v = rand() / (((double)RAND_MAX) + 1.0);
        x = sqrt(-2*log(u)) * cos(2 * pi * v);

        if (std::isfinite(x)){
            //LOG << x <<" ";
        }
    }
    if (x < 2 && x > -2){
        return x/2; // normalize
    }
    else{
        return d_normal();
    }
}

void MainWidget::initializeGL(){
    initializeOpenGLFunctions();
    LOG << (const char*)glGetString(GL_VERSION);

    glClearColor(0, 0, 0, 1);
    initShaders();

    //Light settings
    shaderprogram.setUniformValue("u_ambientLight_strength", 0.15f);
    shaderprogram.setUniformValue("u_specularLight_strength", 1.0f);
    shaderprogram.setUniformValue("u_lightPos", vec3(0,6,0));
    shaderprogram.setUniformValue("u_lightColor", vec3(1,1,1));

    Camera::current = &m_Camera;
    Camera::current->position = {0,1,10};

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    timer.start(12, this);
    m_Rendercount.start();

    Mesh *meshs[] = {new Mesh(":/models/room.obj")};
    Texture *textures[] = {new Texture(Image(":textures/room.png").mirrored())};

    if(QApplication::arguments().size() > 1){
        QFile file(QApplication::arguments()[1]);
        if(!file.open(QIODevice::ReadOnly)){
            return;
        }
        auto rooms = QString(file.readAll().data()).split("\n");
        rooms.removeFirst();
        float x = 0;
        unsigned i = 0;
        for(auto &room : rooms){
            auto objs = room.split(" ");
            objs.removeFirst();
            LOG << objs;

            for(unsigned k = 0; k < objs.size(); k += 3){
                int media = objs[k + 1].toInt();
                int desvio = objs[k + 2].toInt();

                LOG << round(media + d_normal()*desvio);
            }

            //Load Entities
            entities.push_back(new Entity(meshs[0], &shaderprogram));
            entities[i]->m_Texture = textures[0];
            entities[i]->m_Texture->setMinificationFilter(Texture::Nearest);
            entities[i]->m_Texture->setMagnificationFilter(Texture::Linear);
            entities[i]->m_Texture->setWrapMode(Texture::Repeat);

            entities[i]->transform.scale(3);
            entities[i]->position = {x,0,0};
            x += 30;
            i++;
        }
    }

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
    const float zNear = 1.0, zFar = 500.0, fov = 45.0;

    m_Camera.projection.setToIdentity();
    m_Camera.projection.perspective(fov, aspectRatio, zNear, zFar);
}

void MainWidget::paintGL(){
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //transfer view position to light
    shaderprogram.setUniformValue("u_viewPos", Camera::current->position);

    // Set modelview-projection matrix -> Projection * View * Model
    shaderprogram.setUniformValue("u_Projection", Camera::current->projection);
    shaderprogram.setUniformValue("u_View", Camera::current->worldToViewMatrix());

    //for(auto entity : entities) m_Renderer.submit(entity);
    m_Renderer.submit(entities); //submit entire list
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
        //entities[2]->transform.rotate(1,{0,1,0});
        //entity->transform.translate({0,0,0.01f});

    }

    if(m_Rendercount.timetoTick){
        m_Rendercount.timetoTick = false;
        setWindowTitle("Orbal Engine | FPS: " + QString::number(m_Rendercount.getFPS()) + ", UPS: " + QString::number(m_Rendercount.getUPS()));
    }

    // Request an update and swap buffers
    update();
}
