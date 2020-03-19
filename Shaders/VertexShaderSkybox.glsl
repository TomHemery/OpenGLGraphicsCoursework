#version 330 core
//vertex shader used by skybox
//takes in position from the buffers
layout (location = 0) in vec3 aPos;
//outputs a tex coordinate to the fragment shader 
out vec3 TexCoords;
//projection and view matrices
uniform mat4 projection;
uniform mat4 view;

void main()
{
	//get tex coordinates
    TexCoords = aPos;
	//work out position
    vec4 pos = projection * view * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}  