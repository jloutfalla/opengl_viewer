#pragma once
#include "shader.h"

namespace vw
{
    class ShaderProgram
    {
        Shader *vertex;
        Shader *fragment;
        unsigned int object_id{0};

    public:
        ShaderProgram(Shader *vertex, Shader *fragment);
        ~ShaderProgram();
        void load_and_compile();
        void use();

        unsigned int get_object_id();

        void set_unif_4f(const char* name, float x, float y, float z, float w);
    };
} // namespace vw
