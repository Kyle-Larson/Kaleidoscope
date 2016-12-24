#ifndef _H_DEVICE_PROGRAM_
#define _H_DEVICE_PROGRAM_
#include <string>
#include <memory>
#include <vector>
#include <Glew.h>

namespace Device {

    class Program
    {
    public:
        class Shader
        {
        public:
            enum Type : GLenum {
                Vertex = GL_VERTEX_SHADER,
                TessControl = GL_TESS_CONTROL_SHADER,
                TessEvaluation = GL_TESS_EVALUATION_SHADER,
                Geometry = GL_GEOMETRY_SHADER,
                Fragment = GL_FRAGMENT_SHADER
            };

            Shader(Type type);
            Shader(const Shader& shader) = delete;
            Shader(Shader&& shader);

            Shader& operator=(const Shader& shader) = delete;
            Shader& operator=(Shader&& shader);

            ~Shader();

            void SetSource(GLsizei count, const GLchar** sourceCodes, const GLint* lengths);
            void SetSource(const GLchar* sourceCode, GLint length = -1);
            void SetSource(const std::string& sourceCode);

            bool Compile();

            std::vector<char> GetInfoLog() const;

            GLuint GetID() const;

        private:
            enum ShaderParameter : GLenum {
                ShaderType = GL_SHADER_TYPE,
                DeleteStatus = GL_DELETE_STATUS,
                CompileStatus = GL_COMPILE_STATUS,
                InfoLogLength = GL_INFO_LOG_LENGTH,
                ShaderSourceLength = GL_SHADER_SOURCE_LENGTH
            };

            GLuint m_ID;
        };
        Program();
        Program(const Program& program) = delete;
        Program(Program&& program);

        Program& operator=(const Program& program) = delete;
        Program& operator=(Program&& program);

        ~Program();

        void AttachShader(const std::shared_ptr<Shader>& shader);
        void DetachShader(const std::shared_ptr<Shader>& shader);

        bool Link();

        std::vector<char> GetInfoLog() const;

        void Bind();

        GLuint GetID() const;

    private:
        enum ProgramParameter : GLenum {
            DeleteStatus = GL_DELETE_STATUS,
            LinkStatus = GL_LINK_STATUS,
            ValidateStatus = GL_VALIDATE_STATUS,
            InfoLogLength = GL_INFO_LOG_LENGTH,
            AttachedShaders = GL_ATTACHED_SHADERS,
            ActiveAttributes = GL_ACTIVE_ATTRIBUTES,
            ActiveAttributeMaxLength = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
            ActiveUniforms = GL_ACTIVE_UNIFORMS,
            ActiveUniformMaxLength = GL_ACTIVE_UNIFORM_MAX_LENGTH
        };

        GLuint m_ID;
    };

}

#endif