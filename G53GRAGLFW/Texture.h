#pragma once
#include <string>

using namespace std;
//Texture class, used to easily manage opengl textures
class Texture
{
	//ID as given by GL
	unsigned int id;
	//meta data
	int width, height, nrChannels;
public:
	//Constructors
	Texture(string filename);
	~Texture();
	//Methods
	void Use();
};

