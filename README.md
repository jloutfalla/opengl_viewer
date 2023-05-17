# opengl_viewer

install glew, glfw, libmesa => dev et lib


# TODO

- Instead of checking at each setUniform in ShaderProgram if the name exists before setting the value, 
    use something like a class that encapsulate the name, check only once for this ShaderProgram if name exists, then 
    make it easily accessible to change its value.
- make it easier to pass shader program 