#pragma once

#ifdef GLES3
#include <QOpenGLExtraFunctions>
typedef QOpenGLExtraFunctions OpenGLFunc;
#else
#include <QOpenGLFunctions>
typedef QOpenGLFunctions OpenGLFunc;
#endif
