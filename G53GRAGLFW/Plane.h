#pragma once
#include "DisplayableObject.h"
#include <vector>
#include <glm/glm.hpp>

using namespace std;

class Texture;
//LEGACY - plane class that was originally used in place of the rock
class Plane :
	public DisplayableObject
{
	static vector<float> vertices;

	static unsigned int VAO;
	static unsigned int VBO;

	static bool LoadedTextureAndBuffers;

	static Texture * diffuse;
	static Texture * specular;

public:
	Plane(float x, float y, float z);
	~Plane();

	void Display(glm::mat4 model);
};