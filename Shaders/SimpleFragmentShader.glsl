#version 330 core
//used by Embers, shooting stars, takes in a colour and passes it straight to output
out vec4 FragColor;
uniform vec4 colour;
  
void main()
{
	FragColor = colour;
}