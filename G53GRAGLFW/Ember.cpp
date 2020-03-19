#include "Ember.h"
#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ShaderCompiler.h"
#include <random>
//Initialisation and declaration
unsigned int Ember::VAO;
unsigned int Ember::VBO;
Shader * Ember::emberShader = nullptr;

Ember::Ember(glm::vec4 startColour)
{
	//set our velocity to initially just point upwards (relative to parent)
	vel = glm::vec3(0, 3, 0);
	acc = glm::vec3(0, 0, 0);
	colour = startColour;

	//if we don't yet have a static shader, then we must make one (and Buffers) for all embers to use 
	if (emberShader == nullptr) {
		//generate vertex arrays and buffers
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		//create a shader using the handy dandy compiler class
		emberShader = ShaderCompiler::CreateProgram("SimpleVertexShader.glsl", "SimpleFragmentShader.glsl");
	}
}


Ember::~Ember()
{
}

void Ember::Display(glm::mat4 model){
	//use the shader 
	emberShader->Use();
	//set the colour
	emberShader->SetVec4("colour", colour);
	//calculate a model matrix based on the parent model matrix 
	emberShader->SetMat4("model", transform->ApplyToMatrix(model));
	//draw a cube 
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Ember::Update(const float& deltaTime) {
	//calculate position based on acceleration and velocity
	vel += (acc * deltaTime);
	transform->position += vel * deltaTime;
	timeAlive += deltaTime;
	
	//reduce our scale based on the time we have left alive
	transform->scale = glm::vec3(1 - timeAlive / lifeSpan);

	//generate a random acceleration for the next update using a mersenne twister random number generator
	static std::mt19937 twister(glfwGetTime());
	static std::uniform_real_distribution<double> distr(-1, 1);
	acc = glm::vec3(distr(twister), distr(twister), distr(twister));
	acc = acc * 20.f; //increase the scale of peturbation
}

bool Ember::Finished() {
	//return true if the time alive is greater than the life span
	return timeAlive > lifeSpan;
}