#include "Window/Factory.hpp"

namespace Window {

    Factory::Factory()
    {
        if (!glfwInit())
        {
            //iunno, handle error
        }
    }

    Factory::~Factory()
    {
        for (auto& window : m_windows)
        {
            if (auto wind = window.lock())
            {
                wind->~Window();
            }
        }
        glfwTerminate();
    }

    void Factory::ResetHints()
    {
        glfwDefaultWindowHints();
    }

    void Factory::SetHint(WindowHintName name, int value)
    {
        glfwWindowHint(name, value);
    }

    std::shared_ptr<Window> Factory::CreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, Window* share)
    {
        GLFWwindow* ptr = nullptr;
        if (share)
        {
            ptr = share->GetRawHandle();
        }
        return std::make_shared<Window>(glfwCreateWindow(width, height, title, monitor, ptr));
    }

}