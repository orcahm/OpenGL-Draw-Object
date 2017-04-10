#version 430 core                           //lower your version if GLSL 4.5 is not supported by your GPU
in vec2 position;

void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
}