#include <fstream>
#include <filesystem>
#include <GL/glew.h>

#include "viewer_core/shader.h"

namespace fs = std::filesystem;

namespace vw
{
    Shader::Shader(std::string shader_filename, unsigned int shader_type)
        : filename(shader_filename), shader_type(shader_type) {}

    Shader::~Shader()
    {
        this->gl_delete();
    }

    void Shader::gl_delete() {
        glDeleteShader(this->shader_object_id);
        this->shader_object_id = 0;
    }

    bool Shader::load_and_compile()
    {
        fs::path cwd = fs::current_path();
        std::cout << "[WARNING] FIX RELATIVE PATH IN SHADER LOADER" << std::endl;
        auto shaders_dir = cwd / "shaders";

        auto full_path_shader = fs::absolute(shaders_dir / this->filename);

        if (!fs::exists(full_path_shader))
        {
            std::cout << "[Error] Shader path does not exists :" << std::endl
                      << full_path_shader << std::endl;
            return -1;
        }

        std::fstream fs{full_path_shader};
        std::string shader_program, buffer;
        while (std::getline(fs, buffer))
            shader_program += buffer + "\n";

        this->shader_object_id = glCreateShader(this->shader_type);

        const auto shader_program_char = shader_program.c_str();
        glShaderSource(this->shader_object_id, 1, &shader_program_char, NULL);
        glCompileShader(this->shader_object_id);

        int success;
        glGetShaderiv(this->shader_object_id, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(this->shader_object_id, 512, NULL, infoLog);
            std::cout << "[ERROR] Shader Compilation Failed" << std::endl
                      << infoLog << std::endl;
        }

        std::cout << "[SUCCESS] Shader '" << this->filename << "' loaded " << std::endl;
        this->is_loaded = true;
        return true;
    }

    const std::string &Shader::get_filename() const
    {
        return this->filename;
    }
    unsigned int Shader::get_object_id() const
    {
        return this->shader_object_id;
    }
    bool Shader::get_is_loaded() const
    {
        return this->is_loaded;
    }
    unsigned int Shader::get_shader_type() const
    {
        return this->shader_type;
    }
}