#include <GL/glew.h>

#include "viewer_core/program.h"

namespace vw
{
    Program::Program(Shader* vertex, Shader* fragment) : vertex(vertex), fragment(fragment)
    {
    }

    void Program::load_and_compile()
    {
        this->object_id = glCreateProgram();
        glAttachShader(this->object_id, this->vertex->get_object_id());
        glAttachShader(this->object_id, this->fragment->get_object_id());
        glLinkProgram(this->object_id);

        int success;
        glGetProgramiv(this->object_id, GL_LINK_STATUS, &success);

        if (!success)
        {
            char log[512];
            glGetProgramInfoLog(this->object_id, 512, NULL, log);
            std::cout << "[ERROR] Shader Program Linking failed" << std::endl
                      << log << std::endl;
            exit(-1);
        }
        std::cout << "[SUCCESS] Shader Program Linked" << std::endl;
    }

    void Program::gl_delete_shaders()
    {
        this->vertex->gl_delete();
        this->fragment->gl_delete();
    }

    void Program::use()
    {
        glUseProgram(this->object_id);
    }

} // namespace vw
