#include "Device/Device.hpp"

namespace Device {

    Device::Device()
    {
        glewExperimental = true;
        GLenum err = glewInit();
        if (err != GLEW_OK)
        {
            //Handle error
        }
    }

    Device::~Device()
    {
        //Iunno, delete buffers when you can.
        for (auto& buffer : m_buffers)
        {
            if (auto buff = buffer.lock())
            {
                buff->~Buffer();
            }
        }
        for (auto& vertexArray : m_vertexArrays)
        {
            if (auto vertArray = vertexArray.lock())
            {
                vertArray->~VertexArray();
            }
        }
    }

    std::shared_ptr<VertexArray> Device::GenVertexArray()
    {
        GLuint ID;
        glGenVertexArrays(1, &ID);
        auto ptr = std::make_shared<VertexArray>(ID);
        m_vertexArrays.push_back(ptr);
        return ptr;
    }

    std::vector<std::shared_ptr<VertexArray>> Device::GenVertexArrays(GLsizei numVertexArrays)
    {
        std::vector<GLuint> IDs;
        IDs.reserve(numVertexArrays);
        glGenVertexArrays(numVertexArrays, IDs.data());
        std::vector<std::shared_ptr<VertexArray>> vertexArrays;
        vertexArrays.reserve(numVertexArrays);
        for (std::vector<GLuint>::size_type i = 0; i < numVertexArrays; ++i)
        {
            auto ptr = std::make_shared<VertexArray>(IDs[i]);
            vertexArrays[i] = ptr;
            m_vertexArrays.push_back(ptr);
        }
        return vertexArrays;
    }

    std::shared_ptr<Buffer> Device::GenBuffer()
    {
        GLuint ID;
        glGenBuffers(1, &ID);
        auto ptr = std::make_shared<Buffer>(ID);
        m_buffers.push_back(ptr);
        return ptr;
    }

    std::vector<std::shared_ptr<Buffer>> Device::GenBuffers(GLsizei numBuffers)
    {
        std::vector<GLuint> IDs;
        IDs.reserve(numBuffers);
        glGenBuffers(numBuffers, IDs.data());
        std::vector<std::shared_ptr<Buffer>> buffers;
        buffers.reserve(numBuffers);
        for (std::vector<GLuint>::size_type i = 0; i < numBuffers; ++i)
        {
            auto ptr = std::make_shared<Buffer>(IDs[i]);
            m_buffers.push_back(ptr);
            buffers[i] = ptr;
        }
        return buffers;
    }

    std::shared_ptr<Program> Device::GenProgram()
    {
        return std::make_shared<Program>();
    }

    std::shared_ptr<Program::Shader> Device::GenShader(Program::Shader::Type type)
    {
        return std::make_shared<Program::Shader>(type);
    }

    void Device::ClearBuffers(Utility::BitMask<Buffer::Type> mask)
    {
        glClear(mask.GetMask());
    }

    void Device::SetClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
    {
        glClearColor(r, g, b, a);
    }

    void Device::DrawArrays(DrawMode mode, GLint first, GLsizei count)
    {
        glDrawArrays(static_cast<GLenum>(mode), first, count);
    }
}