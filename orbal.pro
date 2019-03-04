QT       += core gui widgets

TARGET = Orbal
TEMPLATE = app

CONFIG += STATIC

SOURCES += main.cpp \
    geometryengine.cpp \
    mainwidget.cpp \
    render/camera.cpp \
    render/entity.cpp \
    render/simplerenderer.cpp \
    render/mesh.cpp


HEADERS += \
    maths/mat.h \
    maths/quaternion.h \
    maths/vec.h \
    opengl/buffer.h \
    opengl/openglfunc.h \
    opengl/shaderprogram.h \
    opengl/texture.h \
    render/camera.h \
    utils/time.h \
    utils/timer.h \
    utils/utils.h \
    geometryengine.h \
    mainwidget.h \
    render/entity.h \
    render/renderer.h \
    render/simplerenderer.h \
    render/mesh.h

RESOURCES += \
    resources/shaders.qrc \
    resources/textures.qrc \
    resources/models.qrc

# install
target.path = $$PWD
INSTALLS += target

DISTFILES +=

#CONFIG += c++11
#LIBS   += -lopengl32
