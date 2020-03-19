#pragma once
#include "Light.h"
#include <string>
#include <vector>

using namespace std;

class Shader;
class ShootingStar :
	public Light
{
	//bit gross, but this is I think the right way to draw a cube 
	//could use an EBO and less vertices - would be more memory efficient, but we only use this once 
	float cubeVertices[108] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
	};

	//Vertex array and buffer objects for rendering 
	static unsigned int VAO;
	static unsigned int VBO;
	//Shader for rendering 
	static Shader * shootingStarShader;
	//Colour for this star
	glm::vec4 colour;

	//information about finding ourself in the shader 
	unsigned int index;
	Shader * registeredShader = nullptr;
	string indexedPointLightArrayName;

	//velocity and lifespan
	glm::vec3 vel;
	float timeAlive = 0.f;
	float lifeSpan = 5.0f;

	//trail
	vector<glm::vec4> trail;
	const float trailPointLifeSpan = 2.f;
public:
	//constructors
	ShootingStar();
	~ShootingStar();
	//methods
	void Update(const float& deltaTime);
	void Display(glm::mat4 model);
	void UpdateShader(int _index, Shader& s);
	//getters
	bool Finished();
};

