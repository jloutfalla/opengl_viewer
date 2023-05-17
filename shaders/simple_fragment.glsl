#version 330 core
// in vec4 position;
out vec4 FragColor;

uniform vec4 interpolation_k;
void main()
{
    // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    FragColor = interpolation_k;
    //FragColor = position;
} 