#ifndef _H_WINDOW_WINDOW_
#define _H_WINDOW_WINDOW_
#include <GLFW\glfw3.h>

namespace Window {

    class Window {
    public:
        Window(GLFWwindow* windowHandle);
        Window(const Window& window) = delete;
        Window(Window&& window);

        Window& operator=(const Window& window) = delete;
        Window& operator=(Window&& window);

        ~Window();

        const GLFWwindow* GetRawHandle() const;
        GLFWwindow* GetRawHandle();
        bool ShouldClose() const;
        void MakeContextCurrent();
        void SetKeyCallbackFunction(GLFWkeyfun callback);

        void SwapBuffers();
    private:
        GLFWwindow* m_windowHandle;
    };

}

#endif