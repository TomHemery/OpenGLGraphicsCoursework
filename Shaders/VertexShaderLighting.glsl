#version 330 core
//vertex shader used by all lit objects in the scene 
//buffer supplied information
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
//output information (sent to fragment shader)
out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
//model view and projection uniforms, passed in from program
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//works out fragment position and normal, sets up gl_position of vertex, and sets tex coordinates
void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    
    gl_Position = projection * view * vec4(FragPos, 1.0);

	TexCoords = aTexCoords;
}