#include <GL/glew.h>

#include "viewer_core/shader_program.h"

namespace vw
{
    ShaderProgram::ShaderProgram(Shader *vertex, Shader *fragment) : vertex(vertex), fragment(fragment)
    {
    }

    ShaderProgram::~ShaderProgram()
    {
        this->vertex->gl_delete();
        this->fragment->gl_delete();
        glDeleteProgram(this->object_id);
    }

    void ShaderProgram::load_and_compile()
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

    void ShaderProgram::use()
    {
        glUseProgram(this->object_id);
    }

    unsigned int ShaderProgram::get_object_id()
    {
        return this->object_id;
    }

    void ShaderProgram::set_unif_4f(const char *name, float x, float y, float z, float w)
    {
        int id = glGetUniformLocation(this->object_id, name);
        if (id == -1)
            std::cout << "[ERROR] uniform location '" << name << "' not found " << std::endl;

        glUniform4f(id, x, y, z, w);
    }

} // namespace vw
