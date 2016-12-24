#ifndef _H_DEVICE_BOOLEAN_
#define _H_DEVICE_BOOLEAN_
#include <Glew.h>

namespace Device {

    enum class Boolean : GLboolean {
        True = GL_TRUE,
        False = GL_FALSE
    };

}

#endif
