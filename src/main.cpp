#include <stdio.h>
#define GLFW_INCLUDE_VLUKAN
#include <GLFW/glfw3.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

int main() {
    if (!glfwInit()) {
        return -1;
    }
    printf("Hello, world!");
    glfwTerminate();
    return 0;
}