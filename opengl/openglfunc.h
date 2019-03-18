#pragma once

#ifdef GLES3
    #include <QOpenGLExtraFunctions>
    typedef QOpenGLExtraFunctions OpenGLFunc;
#else
    #ifdef GL33
        #include <QOpenGLFunctions_3_3_Core>
        typedef QOpenGLFunctions_3_3_Core OpenGLFunc;
    #else
        #include <QOpenGLFunctions>
        typedef QOpenGLFunctions OpenGLFunc;
    #endif
#endif
