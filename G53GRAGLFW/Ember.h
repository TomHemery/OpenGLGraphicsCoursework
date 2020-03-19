#pragma once
#include <glm/common.hpp>
#include "DisplayableObject.h"
class Shader;
class Transform;
//Class to represent an Ember as produced by the ember particle systems attached to each lamp
class Ember : public DisplayableObject
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
	static Shader * emberShader;
	//Colour for this ember
	glm::vec4 colour;

	//velocity and acceleration for simple movement 
	glm::vec3 vel;
	glm::vec3 acc;

	//lifespan information
	float lifeSpan = 3.f;
	float timeAlive = 0.f;

public:
	//Constructors
	Ember(glm::vec4 startColour);
	~Ember();
	//Methods
	void Display(glm::mat4);
	void Update(const float& deltaTime);
	//Getters
	bool Finished();
};

