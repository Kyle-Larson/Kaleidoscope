#ifndef _H_DEVICE_DATATYPE_
#define _H_DEVICE_DATATYPE_
#include <Glew.h>

namespace Device {

    enum class DataType : GLenum {
        Byte = GL_BYTE,
        UnsignedByte = GL_UNSIGNED_BYTE,
        Short = GL_SHORT,
        UnsignedShort = GL_UNSIGNED_SHORT,
        Fixed = GL_FIXED,
        Float = GL_FLOAT
    };

}

#endif