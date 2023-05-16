// include glew BEFORE glfw3
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "viewer_core/shader.h"
#include "viewer_core/program.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  
void error_callback(int error, const char *description)
{
    std::cout << "Error: " << description << std::endl;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    if (!glfwInit())
    {
        std::cout << "GLFW Initilisation failed! " << std::endl;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
    glfwSetErrorCallback(error_callback);
    
    glfwMakeContextCurrent(window);
    
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));

    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    glViewport(0, 0, 800, 600);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };  
    unsigned int VBO;
    glGenBuffers(1, &VBO);  
    glBindBuffer(GL_ARRAY_BUFFER, VBO);  
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    vw::Shader vertex_shader{"simple_vertex.glsl", GL_VERTEX_SHADER};
    vertex_shader.load_and_compile();
    vw::Shader fragment_shader{"simple_fragment.glsl", GL_FRAGMENT_SHADER};
    fragment_shader.load_and_compile();
    
    vw::Program program {&vertex_shader, &fragment_shader};
    program.load_and_compile();
    program.gl_delete_shaders();



    // unsigned int shader_program;
    // shader_program = glCreateProgram();
    // glAttachShader(shader_program, vertex_shader.get_object_id());
    // glAttachShader(shader_program, fragment_shader.get_object_id());
    // glLinkProgram(shader_program);
    
    // int success;
    // glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    // if(!success) {
    //     char log[512];
    //     glGetProgramInfoLog(shader_program, 512, NULL, log);
    //     std::cout << "[ERROR] Shader Program Linking failed" << std::endl << log << std::endl;
    //     return -1; 
    // }   
    // std::cout << "[SUCCESS] Shader Program Linked" << std::endl;

    // glUseProgram(shader_program);
    
    // // clear loaded shader program
    // vertex_shader.gl_delete();
    // fragment_shader.gl_delete();


    /*
        first arg '0': 
        layout(location=0) in vertex shader, tell to opengl that the GL_ARRAY_BUFFER currently bound 
        should go to location 0 in the shader program

        '3':
        nomber of element in the vertex, this time 3, see vertices

        'GL_FLOAT':
        type on a single element of the vertex

        'GL_FALSE':
        If that should be normalized to float, [-1, 1] if signed [0, 1] otherwise

        '0':
        tricky part, if the vertices passed to the currently bound GL_ARRAY_BUFFER are
        tighlty packed then '0' let opengl compute the stride, or step between each vertex.
        otherwise we have to manually specify it, in this case: sizeof(float)*3

        '(void*) 0':
        weird cast, position data begins in the buffer.
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    // enable the vertex attribute giving the vertex attribute location : vertex attributes are disabled by default
    glEnableVertexAttribArray(0);


    program.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);


    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }   

    glfwTerminate();
    return 0;
}