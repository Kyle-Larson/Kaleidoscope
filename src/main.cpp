#include <stdio.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define GLEW_STATIC
#include <gl/glew.h>
#include <GLFW/glfw3.h>

GLFWwindow* g_mainWindow;
GLuint vertexBuffer, vertexShader, fragmentShader, program;
GLint mvp_location, vpos_location, vcol_location;

static const struct
{
    float x, y;
    float r, g, b;
} vertices[3] =
{
    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
    { 0.6f, -0.4f, 0.f, 1.f, 0.f },
    { 0.f, 0.6f, 0.f, 0.f, 1.f }
};

static const char* vertex_shader_text =
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"   gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"   color = vCol;\n"
"}\n";

static const char* fragment_shader_text =
"varying vec3 color;\n"
"void main()\n"
"{\n"
"   gl_fragColor = vec4(color, 1.0);\n"
"}\n";

static void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

static void input_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void loop(void) {
    double time = glfwGetTime();
    glfwPollEvents();


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

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return -1;
    }

    glfwSetKeyCallback(g_mainWindow, input_callback);
    glfwMakeContextCurrent(g_mainWindow);
    glfwSwapInterval(1);

    int width, height;
    glfwGetFramebufferSize(g_mainWindow, &width, &height);
    glViewport(0, 0, width, height);


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