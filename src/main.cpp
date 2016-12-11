#include <stdio.h>
#include <string>
#include <vector>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define GLEW_STATIC
#include <gl/glew.h>
#include <GLFW/glfw3.h>

GLFWwindow* g_mainWindow;
GLuint VertexArrayID;
GLuint vertexBuffer;
GLuint programID;

static void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

static void input_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

GLuint LoadShaders(const char* vertexFilePath, const char* fragmentFilePath) {

    //Create shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    std::string VertexShaderCode = "attribute vec3 vertexPosition_modelspace;\nvoid main(){\ngl_Position.xyz = vertexPosition_modelspace;\ngl_Position.w = 1.0;\n}";
    std::string FragmentShaderCode = "void main() {\ngl_FragColor = vec4(1,0,0,1);\n}";

    GLint result = GL_FALSE;
    int InfoLogLength;

    printf("Compiling shader : %s\n", vertexFilePath);
    char const* VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);

    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ) {
        std::vector<char> VertexShaderErrorMessage = std::vector<char>(InfoLogLength + 1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    printf("Compiling shader : %s\n", fragmentFilePath);
    char const* FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);

    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ) {
        std::vector<char> FragmentShaderErrorMessage = std::vector<char>(InfoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    glGetProgramiv(ProgramID, GL_LINK_STATUS, &result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ) {
        std::vector<char> ProgramErrorMessage = std::vector<char>(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

void loop(void) {
    double time = glfwGetTime();
    glfwPollEvents();

    glClear( GL_COLOR_BUFFER_BIT );

    glUseProgram(programID);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);


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
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    programID = LoadShaders("VertexShaderFile", "FragmentShaderFile");

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(loop, 0, 1);
    #else
        while(!glfwWindowShouldClose(g_mainWindow))
        {
            loop();
        }
    #endif

    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);


    glfwTerminate();
    return 0;
}