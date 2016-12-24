#include "Window/Window.hpp"
#include <utility>

namespace Window {

    Window::Window(GLFWwindow* windowHandle)
        : m_windowHandle(windowHandle) { }

    Window::Window(Window&& window)
        : m_windowHandle(window.m_windowHandle)
    {
        window.m_windowHandle = nullptr;
    }

    Window& Window::operator=(Window&& window)
    {
        std::swap(m_windowHandle, window.m_windowHandle);
        return *this;
    }

    Window::~Window()
    {
        if (m_windowHandle)
        {
            glfwDestroyWindow(m_windowHandle);
        }
        m_windowHandle = nullptr;
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_windowHandle) != 0;
    }

    void Window::MakeContextCurrent()
    {
        glfwMakeContextCurrent(m_windowHandle);
    }

    void Window::SetKeyCallbackFunction(GLFWkeyfun callback)
    {
        glfwSetKeyCallback(m_windowHandle, callback);
    }

    const GLFWwindow* Window::GetRawHandle() const
    {
        return m_windowHandle;
    }

    GLFWwindow* Window::GetRawHandle()
    {
        return m_windowHandle;
    }

    void Window::SwapBuffers()
    {
        glfwSwapBuffers(m_windowHandle);
    }

}