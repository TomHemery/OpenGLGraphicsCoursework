#pragma once
#include "Light.h"
#include <string>

using namespace std;

class MeshRenderer;
class EmberSystem;

//Lantern class - loads a lantern model, emits particles and emits a light that flickers 
class Lantern :
	public Light
{
	//rendering
	static MeshRenderer * LanternModel;

	//information about finding ourself in the shader 
	unsigned int index;
	Shader * registeredShader = nullptr;
	string indexedPointLightArrayName;

	//a little offset to push the source of the light up a bit 
	int lightSourceOffset = 1;

	//an ember particle system
	EmberSystem * mEmberSystem;

public:
	//Constructors 
	Lantern(float x, float y, float z);
	~Lantern();
	//Methods
	void Display(glm::mat4 model);
	void Update(const float& deltaTime);
	void UpdateShader(int _index, Shader& s);
	//Setters
	void SetColour(float r, float g, float b);
};

