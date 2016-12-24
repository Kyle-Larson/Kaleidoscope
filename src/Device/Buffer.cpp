#include "Device/Buffer.hpp"

#include <utility>

namespace Device {

    Buffer::Buffer(GLuint buffID) : m_ID(buffID)
    { }

    Buffer::Buffer(Buffer&& buffer) : m_ID(buffer.m_ID)
    {
        buffer.m_ID = 0;
    }

    Buffer& Buffer::operator=(Buffer&& buffer)
    {
        std::swap(m_ID, buffer.m_ID);
        return *this;
    }

    Buffer::~Buffer()
    {
        glDeleteBuffers(1, &m_ID);
    }

    void Buffer::Bind(Buffer::Target target)
    {
        glBindBuffer(static_cast<GLenum>(target), m_ID);
    }

    void Buffer::SetData(Buffer::Target target, GLsizeiptr size, const GLvoid* data, Buffer::Usage usage)
    {
        glBufferData(static_cast<GLenum>(target), size, data, static_cast<GLenum>(usage));
    }

    GLuint Buffer::GetID() const
    {
        return m_ID;
    }
}