#include <iostream>

#include "viewer_core/viewer.h"

namespace vw
{
    void error_callback(int error, const char *description)
    {
        std::cout << "[Error] " << description << std::endl;
    }

    void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    Viewer::Viewer(int width, int height)
    {
        if (!glfwInit())
        {
            std::cerr << "[ERROR] GLFW Initilisation failed! " << std::endl;
            exit(-1);
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        this->window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);

        if (!window)
        {
            std::cerr << "[ERROR] Failed to create GLFW window" << std::endl;
            glfwTerminate();
            exit(-1);
        }

        glfwMakeContextCurrent(window);

        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            /* Problem: glewInit failed, something is seriously wrong. */
            std::cerr << "[ERROR] " << glewGetErrorString(err) << std::endl;
            exit(-1);
        }
        std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

        glViewport(0, 0, width, height);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        this->setup_callbacks();
    }

    Viewer::~Viewer()
    {
        glfwTerminate();
    }

    void Viewer::setup_callbacks()
    {
        glfwSetErrorCallback(error_callback);
        glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
    }
} // namespace vw
