#include <fstream>
#include <filesystem>

#include "viewer_core/shader.h"

namespace fs = std::filesystem;


namespace vw
{
    Shader::Shader(std::string s) : filename(s) {}


    bool Shader::prepare()
    {
        fs::path cwd = fs::current_path();
        std::cout << cwd << std::endl;
        auto shaders_dir = cwd.parent_path().parent_path() / "shaders";

        auto full_path_shader = fs::absolute(shaders_dir / this->filename);

        if (!fs::exists(full_path_shader))
        {
            std::cout << "Error: shader path does not exists " << std::endl
                      << full_path_shader << std::endl;
            return -1;
        }

        std::fstream fs{full_path_shader};
        std::string file, buffer;
        while (std::getline(fs, buffer))
        {
            file += buffer;
        }

        std::cout << file << std::endl;

        return true;
    }
}