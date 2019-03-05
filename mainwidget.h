#pragma once

#include "render/entity.h"
#include "render/simplerenderer.h"

#include <QOpenGLWidget>
#include "opengl/openglfunc.h"
#include "maths/mat.h"
#include "maths/quaternion.h"
#include "maths/vec.h"
#include "utils/timer.h"
#include "opengl/shaderprogram.h"
#include "opengl/texture.h"
#include "utils/time.h"
#include "render/camera.h"

class MainWidget : public QOpenGLWidget, protected OpenGLFunc{
    Q_OBJECT

    Timer timer;
	Camera m_Camera;
	RenderCount m_Rendercount;
	SimpleRenderer m_Renderer;
	
    Vec2 m_MousePressPosition;
	
    ShaderProgram shaderprogram;
    
    std::vector<Entity*> entities;

    Texture *texture;

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

protected:
    //events
    void mouseMoveEvent(QMouseEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    void timerEvent(QTimerEvent *e) override;

    //initialize
    void initializeGL() override;
    //event resizewindow
    void resizeGL(int w, int h) override;
    //loop render
    void paintGL() override;

    void initShaders();
    void initTextures();

};

