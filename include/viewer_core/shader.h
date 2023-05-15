#pragma once
#include <iostream>


namespace vw
{
    class Shader
    {
        std::string filename;
        unsigned int shader_object{0};
        bool prepared{false};

    public:
        Shader(std::string s);
        bool prepare();
    };
}