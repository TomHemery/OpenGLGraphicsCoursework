#include "Texture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>

Texture::Texture(string filename)
{
	//Work out the path
	string path = "../Textures/" + filename;
	//Generate the rextures
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load the texture using STBI (lovely library)
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	//it worked
	if (data)
	{
		cout << "Created texture from " << filename << " with dimensions: " << width << ", " << height << " Num channels: " << nrChannels << endl;
		glTexImage2D(GL_TEXTURE_2D, 0, (nrChannels == 3 ? GL_RGB : GL_RGBA), width, height, 0, (nrChannels == 3 ? GL_RGB : GL_RGBA), GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	//it didn't
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	} 
	//free it up
	stbi_image_free(data);
}

Texture::~Texture()
{

}

void Texture::Use() {
	//self explanatory really
	glBindTexture(GL_TEXTURE_2D, id);
}