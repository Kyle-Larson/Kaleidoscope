#ifndef _H_DEVICE_DEVICE_
#define _H_DEVICE_DEVICE_
#include <vector>
#include <memory>
#include <Glew.h>

#include "Device/Buffer.hpp"
#include "Device/VertexArray.hpp"
#include "Device/Program.hpp"
#include "Device/DrawMode.hpp"
#include "Utility/Bitfield.hpp"

namespace Device {

    class Device {
        public:
            Device();
            ~Device();

            std::shared_ptr<VertexArray> GenVertexArray();
            std::vector<std::shared_ptr<VertexArray>> GenVertexArrays(GLsizei numVertexArrays);

            std::shared_ptr<Buffer> GenBuffer();
            std::vector<std::shared_ptr<Buffer>> GenBuffers(GLsizei numBuffers);

            std::shared_ptr<Program> GenProgram();
            std::shared_ptr<Program::Shader> GenShader(Program::Shader::Type type);

            void ClearBuffers(Utility::BitMask<Buffer::Type> mask);
            void SetClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
            void DrawArrays(DrawMode mode, GLint first, GLsizei count);

        private:
            std::vector<std::weak_ptr<Buffer>> m_buffers;
            std::vector<std::weak_ptr<VertexArray>> m_vertexArrays;
            GLuint m_boundVertexArray;
            GLuint m_boundBuffer;
    };

}
#endif