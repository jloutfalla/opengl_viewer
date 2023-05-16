#pragma once
#include <iostream>


namespace vw
{
    class Shader
    {
        std::string filename;
        unsigned int object_id{0};
        bool is_loaded{false};
        unsigned int shader_type;

    public:
        Shader(std::string shader_filename, unsigned int shader_type);
        ~Shader();

        bool load_and_compile();
        void gl_delete();

        const std::string& get_filename() const;
        unsigned int get_object_id() const; 
        bool get_is_loaded() const ;
        unsigned int get_shader_type() const;
    };
}