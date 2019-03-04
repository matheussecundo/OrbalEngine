#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>

#ifndef QT_NO_OPENGL
#include "mainwidget.h"
#endif

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setSwapInterval(0); // vsync
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("Orbal Engine");
    app.setApplicationVersion("0.1");

#ifndef QT_NO_OPENGL
    MainWidget widget;
    widget.resize(1280,720);
    widget.show();
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif

    return app.exec();
}

//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
