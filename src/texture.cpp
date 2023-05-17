// include glew BEFORE glfw3
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>

#include "viewer_core/shader.h"
#include "viewer_core/shader_program.h"
#include "viewer_core/viewer.h"


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, true);
            break;
        case GLFW_KEY_Z:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        case GLFW_KEY_X:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
        default:
            break;
        }
    }
}

int main()
{
    vw::Viewer viewer{800, 600}; 
    glfwSetKeyCallback(viewer.window, key_callback);

    std::vector tex_coords{
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.5f, 1.0f,
    };
    
    std::vector quad {
        // triangle 1
        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        // triangle 2
        1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
    };
    
    unsigned int VAO1;
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);
    
    unsigned int VBO1;
    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * quad.size(), quad.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);  
    glEnableVertexAttribArray(0);

    vw::Shader vertex_shader{"texture.vs", GL_VERTEX_SHADER};
    vertex_shader.load_and_compile();
    vw::Shader fragment_shader{"texture.fs", GL_FRAGMENT_SHADER};
    fragment_shader.load_and_compile();
    vw::ShaderProgram program{&vertex_shader, &fragment_shader};
    program.load_and_compile();
    fragment_shader.gl_delete();
    vertex_shader.gl_delete();
    
    while (!glfwWindowShouldClose(viewer.window))
    {
        glfwSwapBuffers(viewer.window);
        glfwPollEvents();
        
        glClear(GL_COLOR_BUFFER_BIT);

        program.use();
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    return 0;
}