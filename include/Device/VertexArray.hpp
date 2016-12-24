#ifndef _H_DEVICE_VERTEX_ARRAY_
#define _H_DEVICE_VERTEX_ARRAY_
#include <Glew.h>
#include "Device\DataType.hpp"
#include "Device\Boolean.hpp"

namespace Device {

    class VertexArray
    {
        public:
            VertexArray(GLuint vertArrayID);
            VertexArray(const VertexArray& vertArray) = delete;
            VertexArray(VertexArray&& vertArray);

            VertexArray& operator=(const VertexArray& vertArray) = delete;
            VertexArray& operator=(VertexArray&& vertArray);

            ~VertexArray();

            GLuint GetID() const;
            void Bind();

            void EnableAttributeArray(GLuint index);
            void DisableAttributeArray(GLuint index);
            void SetAttributeArray(
                GLuint index,
                GLint attributeSize,
                DataType attributeType,
                Boolean isNormalized,
                GLsizei dataStride,
                const GLvoid* dataPointer);

        private:
            GLuint m_ID;
    };

}
#endif