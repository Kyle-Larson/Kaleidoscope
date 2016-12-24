#ifndef _H_WINDOW_FACTORY_
#define _H_WINDOW_FACTORY_
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>
#include "Window/Window.hpp"

namespace Window {

    class Factory {
        using WindowHintName = int;
    public:
        Factory();
        ~Factory();

        void ResetHints();
        void SetHint(WindowHintName Hint, int value);
        std::shared_ptr<Window> CreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, Window* share);
    private:
        std::vector<std::weak_ptr<Window>> m_windows;
    };

}

#endif