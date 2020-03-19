#version 330 core
//fragment shader used by sky box
out vec4 FragColor;
//takes in tex coordinats from the vertex shader 
in vec3 TexCoords;
//creates a cube sampler to render the texture
uniform samplerCube skybox;

void main()
{    
	//only texture colour is considered
    FragColor = texture(skybox, TexCoords);
}