#include "Device/VertexArray.hpp"

#include <utility>

namespace Device {

    VertexArray::VertexArray(GLuint vertArrayID) : m_ID(vertArrayID)
    { }

    VertexArray::VertexArray(VertexArray&& vertArray) : m_ID(vertArray.m_ID)
    {
        vertArray.m_ID = 0;
    }

    VertexArray& VertexArray::operator=(VertexArray&& vertArray)
    {
        std::swap(m_ID, vertArray.m_ID);
        return *this;
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_ID);
    }

    GLuint VertexArray::GetID() const
    {
        return m_ID;
    }

    void VertexArray::Bind()
    {
        glBindVertexArray(m_ID);
    }

    void VertexArray::EnableAttributeArray(GLuint index)
    {
        glEnableVertexAttribArray(index);
    }

    void VertexArray::DisableAttributeArray(GLuint index)
    {
        glDisableVertexAttribArray(index);
    }

    void VertexArray::SetAttributeArray(
        GLuint index,
        GLint attributeSize,
        DataType attributeType,
        Boolean isNormalized,
        GLsizei dataStride,
        const GLvoid* dataPointer)
    {
        glVertexAttribPointer(
            index,
            attributeSize,
            static_cast<GLenum>(attributeType),
            static_cast<GLboolean>(isNormalized),
            dataStride,
            dataPointer);
    }
}