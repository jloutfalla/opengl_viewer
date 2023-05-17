#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace vw
{

    class Viewer
    {
    public:
        GLFWwindow *window;

        Viewer(int width, int height);
        ~Viewer();

    private:
        void setup_callbacks();
    };
} // namespace vw
