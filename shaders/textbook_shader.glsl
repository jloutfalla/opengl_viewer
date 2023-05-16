#version version_number
in type in_variable_name;
in type in_variable_name;

out type out_variable_name;
  
uniform type uniform_name;

out vec4 vertexColor;
if name and type off output match an input in next shader, say the fragment shader, 
then the fragment shader will receive the variable from the vertex shader.

uniform allow to set global variable among a shader program: meaning all off the shaders inside a program can access it
by using the keyword 'uniform' in front a of variable

uniform vec4 trucmuche;

uniform are set on the cpu.
void main()
{
    // process input(s) and do some weird graphics stuff
    ...
    // output processed stuff to output variable
    out_variable_name = weird_stuff_we_processed;

    // swizzling
    vec2 someVec;
    vec4 differentVec = someVec.xyxx;
    vec3 anotherVec = differentVec.zyw;
    vec4 otherVec = someVec.xxxx + anotherVec.yxzy;
    
    vec2 vect = vec2(0.5, 0.7);
    vec4 result = vec4(vect, 0.0, 0.0);
    vec4 otherResult = vec4(result.xyz, 1.0);

    
}