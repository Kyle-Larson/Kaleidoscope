#include <stdio.h>

#include <GLFW/glfw3.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

GLFWwindow* g_mainWindow;

void loop(void) {

}

int main() {
    if (!glfwInit()) 
    {
        return -1;
    }
    
    //OpenGL ES 2.0 Stuff
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    g_mainWindow = glfwCreateWindow(640, 480, "Hello, World", NULL, NULL);
    if(!g_mainWindow)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(g_mainWindow);

    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(loop, 60, 1);
    #else
        while(!glfwWindowShouldClose(g_mainWindow))
        {
            loop();
        }
    #endif


    glfwTerminate();
    return 0;
}