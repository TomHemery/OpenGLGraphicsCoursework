#pragma once
#include "Animatable.h"
#include <glm/glm.hpp>

class Shader;
//Interface class for lights 
class Light : public Animatable {
public:
	enum LightType { DIRECTIONAL, POINT };
	//Constructors 
	Light() {};
	virtual ~Light() {};
	//Methods
	virtual void Display(glm::mat4 model) = 0;
	virtual void Update(const float& deltaTime) = 0;
	virtual void UpdateShader(int _index, Shader& s) = 0;
protected:
	LightType type;

	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant;
	float linear;
	float quadratic;

public:
	static int numPointLights;
	static const int MAX_POINT_LIGHTS = 32;
};