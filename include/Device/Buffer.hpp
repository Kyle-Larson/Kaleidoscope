#ifndef _H_DEVICE_BUFFER_
#define _H_DEVICE_BUFFER_
#include <Glew.h>

namespace Device {

    class Buffer {
        public:
            enum class Type : GLenum {
                Color = GL_COLOR_BUFFER_BIT,
                Depth = GL_DEPTH_BUFFER_BIT,
                Stencil = GL_STENCIL_BUFFER_BIT
            };

            enum class Usage : GLenum {
                StreamDraw = GL_STREAM_DRAW,
                StreamRead = GL_STREAM_READ,
                StreamCopy = GL_STREAM_COPY,
                StaticDraw = GL_STATIC_DRAW,
                StaticRead = GL_STATIC_READ,
                StaticCopy = GL_STATIC_COPY,
                DynamicDraw = GL_DYNAMIC_DRAW,
                DynamicRead = GL_DYNAMIC_READ,
                DynamicCopy = GL_DYNAMIC_COPY
            };

            enum class Target : GLenum {
                ArrayBuffer = GL_ARRAY_BUFFER,
                AtomicCounterBuffer = GL_ATOMIC_COUNTER_BUFFER,
                CopyReadBuffer = GL_COPY_READ_BUFFER,
                CopyWriteBuffer = GL_COPY_WRITE_BUFFER,
                DrawIndirectBuffer = GL_DRAW_INDIRECT_BUFFER,
                ElementArrayBuffer = GL_ELEMENT_ARRAY_BUFFER,
                PixelPackBuffer = GL_PIXEL_PACK_BUFFER,
                ShaderStorageBuffer = GL_SHADER_STORAGE_BUFFER,
                TextureBuffer = GL_TEXTURE_BUFFER,
                TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
                UniformBuffer = GL_UNIFORM_BUFFER
            };

            Buffer(GLuint bufferID);
            Buffer(const Buffer& buffer) = delete;
            Buffer(Buffer&& buffer);

            Buffer& operator=(const Buffer& buffer) = delete;
            Buffer& operator=(Buffer&& buffer);

            ~Buffer();

            void Bind(Target target);
            void SetData(Target target, GLsizeiptr size, const GLvoid* data, Usage usage);

            GLuint GetID() const;

        private:
            GLuint m_ID;
    };

}
#endif