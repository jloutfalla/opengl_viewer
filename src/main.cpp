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
    
    std::vector Triangle1 {
        // triangle 1
        -0.25f, -0.25f, 0.0f,
        0.25f, -0.25f, 0.0f,
        0.0f, 0.25f, 0.0f,
    };
    unsigned int VAO1;
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);
    
    unsigned int VBO1;
    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Triangle1.size(), Triangle1.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);  
    glEnableVertexAttribArray(0);
    
    std::vector Triangle2 {
        // triangle 2
        0.25f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f, // vertex, color pair
        0.75f, -0.25f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.25f, 0.0f, 0.0f, 0.0f, 1.0f,
    };
    unsigned int VAO2;
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    unsigned int VBO2;
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Triangle2.size(), Triangle2.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (void *)0); 
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (void *)(sizeof(float)*3));  
    glEnableVertexAttribArray(1);

    vw::Shader vertex_shader{"simple_vertex.glsl", GL_VERTEX_SHADER};
    vertex_shader.load_and_compile();
    vw::Shader fragment_shader{"simple_fragment.glsl", GL_FRAGMENT_SHADER};
    fragment_shader.load_and_compile();
    vw::ShaderProgram program{&vertex_shader, &fragment_shader};
    program.load_and_compile();
    fragment_shader.gl_delete();

    vw::Shader fragment_shader_yellow{"simple_yellow_fragment.glsl", GL_FRAGMENT_SHADER};
    fragment_shader_yellow.load_and_compile();
    vw::ShaderProgram program2{&vertex_shader, &fragment_shader_yellow};
    program2.load_and_compile();
    fragment_shader_yellow.gl_delete();
    vertex_shader.gl_delete();
    
    while (!glfwWindowShouldClose(viewer.window))
    {
        glfwSwapBuffers(viewer.window);
        glfwPollEvents();
        
        glClear(GL_COLOR_BUFFER_BIT);

        // glProgramUse before setting uniform
        program.use();
        float time = glfwGetTime();
        float back_forth = sin(time*2)/2.0f+0.5f;
        program.set_unif_4f("interpolation_k",  0.0f, back_forth, 0.0f, 1.0f);

        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        program2.use();
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    return 0;
}