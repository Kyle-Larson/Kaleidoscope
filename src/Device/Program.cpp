#include "Device/Program.hpp"

#include <vector>
#include <utility>
#include <Glew.h>

namespace Device {

    Program::Shader::Shader(Program::Shader::Type type)
        : m_ID(glCreateShader(type))
    { }

    Program::Shader::Shader(Program::Shader&& shader)
        : m_ID(shader.m_ID)
    {
        shader.m_ID = 0;
    }

    Program::Shader& Program::Shader::operator=(Program::Shader&& shader)
    {
        std::swap(m_ID, shader.m_ID);
        return *this;
    }

    Program::Shader::~Shader()
    {
        glDeleteShader(m_ID);
    }

    void Program::Shader::SetSource(GLsizei count, const GLchar** sourceCodes, const GLint* lengths)
    {
        glShaderSource(m_ID, count, sourceCodes, lengths);
    }

    void Program::Shader::SetSource(const GLchar* sourceCode, GLint length)
    {
        glShaderSource(m_ID, 1, &sourceCode, &length);
    }

    void Program::Shader::SetSource(const std::string& sourceCode)
    {
        const GLchar* src = sourceCode.c_str();
        glShaderSource(m_ID, 1, &src, nullptr);
    }

    bool Program::Shader::Compile()
    {
        GLint result;
        glCompileShader(m_ID);

        glGetShaderiv(m_ID, ShaderParameter::CompileStatus, &result);
        return result == GL_TRUE;
    }

    std::vector<char> Program::Shader::GetInfoLog() const
    {
        GLint infoLogLength;
        std::vector<char> infoLogBuffer;
        glGetShaderiv(m_ID, ShaderParameter::InfoLogLength, &infoLogLength);
        infoLogBuffer.reserve(infoLogLength);
        glGetShaderInfoLog(m_ID, infoLogLength, nullptr, infoLogBuffer.data());
        return infoLogBuffer;
    }

    GLuint Program::Shader::GetID() const
    {
        return m_ID;
    }




    Program::Program()
        : m_ID(glCreateProgram())
    { }

    Program::Program(Program&& program)
        : m_ID(program.m_ID)
    {
        program.m_ID = 0;
    }

    Program& Program::operator=(Program&& program)
    {
        std::swap(m_ID, program.m_ID);
        return *this;
    }

    Program::~Program()
    {
        glDeleteProgram(m_ID);
        m_ID = 0;
    }

    void Program::AttachShader(const std::shared_ptr<Shader>& shader)
    {
        glAttachShader(m_ID, shader->GetID());
    }

    void Program::DetachShader(const std::shared_ptr<Shader>& shader)
    {
        glDetachShader(m_ID, shader->GetID());
    }

    bool Program::Link()
    {
        GLint result;
        glLinkProgram(m_ID);
        glGetProgramiv(m_ID, ProgramParameter::LinkStatus, &result);
        return result == GL_TRUE;
    }

    std::vector<char> Program::GetInfoLog() const
    {
        GLint infoLogLength;
        std::vector<char> infoLogBuffer;
        glGetProgramiv(m_ID, ProgramParameter::InfoLogLength, &infoLogLength);
        infoLogBuffer.reserve(infoLogLength);
        glGetProgramInfoLog(m_ID, infoLogLength, nullptr, infoLogBuffer.data());
        return infoLogBuffer;
    }

    void Program::Bind()
    {
        glUseProgram(m_ID);
    }

    GLuint Program::GetID() const
    {
        return m_ID;
    }

}