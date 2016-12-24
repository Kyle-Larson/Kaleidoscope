#ifndef _H_DEVICE_DRAWMODE_
#define _H_DEVICE_DRAWMODE_
#include <Glew.h>

namespace Device {

    enum class DrawMode : GLenum {
        Points = GL_POINTS,
        LineStrip = GL_LINE_STRIP,
        LineLoop = GL_LINE_LOOP,
        Lines = GL_LINES,
        TriangleStrip = GL_TRIANGLE_STRIP,
        TriangleFan = GL_TRIANGLE_FAN,
        Triangles = GL_TRIANGLES
    };

}

#endif