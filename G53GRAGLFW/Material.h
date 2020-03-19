#pragma once
#include <string>
#include <glm/glm.hpp>

using namespace std;

class Texture;

//Class to represent a material for rendering 
class Material
{
	//the name of this material 
	string name;

	//colour information 
	glm::vec3 ambientColour = glm::vec3(0, 0, 0);
	glm::vec3 diffuseColour = glm::vec3(0, 0, 0);
	glm::vec3 specularColour = glm::vec3(0, 0, 0);
	float shininess = 0.f;

	//texture information 
	Texture * diffuseMap = nullptr;
	Texture * specularMap = nullptr;

public:
	Material(const string& _name);
	~Material();
	//getters
	const string& GetName() { return name; }
	//setters
	void SetAmbientColour(glm::vec3 c) { ambientColour = c; }
	void SetDiffuseColour(glm::vec3 c) { diffuseColour = c; }
	void SetSpecularColor(glm::vec3 c) { specularColour = c; }
	void SetShininess(float s) { shininess = s; }
	void SetDiffuseMap(Texture * tex) { diffuseMap = tex; }
	void SetSpecularMap(Texture * tex) { specularMap = tex; }
	//attempts to apply this material's values to the current shader
	void Use();
};