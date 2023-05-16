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
        ~Program();
        void load_and_compile();
        bool gl_delete_shaders();
        void use();

    };
} // namespace vw
