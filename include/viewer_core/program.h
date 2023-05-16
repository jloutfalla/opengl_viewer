#pragma once
#include "shader.h"

namespace vw
{   
    class Program {
        Shader* vertex;
        Shader* fragment;
        unsigned int object_id{0};

    public:
        Program(Shader* vertex, Shader* fragment);
        void load_and_compile();
        void gl_delete_shaders();
        void use();

    };
} // namespace vw
