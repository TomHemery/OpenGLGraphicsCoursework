#version 330 core
//used by embers, shooting stars, takes a position from the buffer
//uses model view and projection to calculate position
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}