#version 330 core

in vec3 aColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(aColor.x, 0.0f, aColor.y, 1.0f);
} 