#include <stdio.h>
#include <string>
#include <vector>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <Glew.h>
#include <GLFW/glfw3.h>

#include "Device/Device.hpp"


GLFWwindow* g_mainWindow;
Device::Device* g_device;
std::shared_ptr<Device::Program> g_shadingProgram;
std::shared_ptr<Device::VertexArray> g_vertexArray;
std::shared_ptr<Device::Buffer> g_vertexBuffer;

static void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

static void input_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

std::shared_ptr<Device::Program> LoadShaders(const char* vertexFilePath, const char* fragmentFilePath)
{

    //Create shaders
    auto vertexShader = g_device->GenShader(Device::Program::Shader::Type::Vertex);
    auto fragmentShader = g_device->GenShader(Device::Program::Shader::Type::Fragment);

    std::string VertexShaderCode = "attribute vec3 vertexPosition_modelspace;\nvoid main(){\ngl_Position.xyz = vertexPosition_modelspace;\ngl_Position.w = 1.0;\n}";
    std::string FragmentShaderCode = "void main() {\ngl_FragColor = vec4(1,0,0,1);\n}";

    vertexShader->SetSource(VertexShaderCode);
    if (!vertexShader->Compile())
    {
        std::vector<char> infoLog = vertexShader->GetInfoLog();
        printf("%s\n", infoLog.data());
    }

    fragmentShader->SetSource(FragmentShaderCode);
    if (!fragmentShader->Compile())
    {
        std::vector<char> infoLog = fragmentShader->GetInfoLog();
        printf("%s\n", infoLog.data());
    }

    auto program = g_device->GenProgram();
    program->AttachShader(vertexShader);
    program->AttachShader(fragmentShader);
    if (!program->Link())
    {
        std::vector<char> infoLog = program->GetInfoLog();
        printf("%s\n", infoLog.data());
    }

    program->DetachShader(vertexShader);
    program->DetachShader(fragmentShader);

    return program;
}

void loop(void) {
    double time = glfwGetTime();
    glfwPollEvents();

    Utility::BitMask<Device::Buffer::Type> mask;
    mask.SetBit(Device::Buffer::Type::Color, true);

    g_device->ClearBuffers(mask);

    g_shadingProgram->Bind();

    g_vertexArray->EnableAttributeArray(0);
    g_vertexBuffer->Bind(Device::Buffer::Target::ArrayBuffer);
    g_vertexArray->SetAttributeArray(
        0,
        3,
        Device::DataType::Float,
        Device::Boolean::False,
        0,
        nullptr);

    g_device->DrawArrays(Device::DrawMode::Triangles, 0, 3);
    g_vertexArray->DisableAttributeArray(0);

    glfwSwapBuffers(g_mainWindow);
}

int main() {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) 
    {
        return -1;
    }
    
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    g_mainWindow = glfwCreateWindow(640, 480, "Hello, World", NULL, NULL);
    if(!g_mainWindow)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(g_mainWindow);

    Device::Device device = Device::Device();

    glfwSetKeyCallback(g_mainWindow, input_callback);
    device.SetClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    g_vertexArray = device.GenVertexArray();
    g_vertexArray->Bind();

    g_shadingProgram = LoadShaders("VertexShaderFile", "FragmentShaderFile");

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    g_vertexBuffer = device.GenBuffer();
    g_vertexBuffer->Bind(Device::Buffer::Target::ArrayBuffer);
    g_vertexBuffer->SetData(Device::Buffer::Target::ArrayBuffer, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, Device::Buffer::Usage::StaticDraw);


    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(loop, 0, 1);
    #else
        while(!glfwWindowShouldClose(g_mainWindow))
        {
            loop();
        }
    #endif

    glfwTerminate();
    return 0;
}