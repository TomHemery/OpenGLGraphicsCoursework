#include "ShootingStar.h"
#include "ShaderCompiler.h"
#include "Shader.h"
#include "Engine.h"
#include "Camera.h"

#include <iostream>
#include <random>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>

unsigned int ShootingStar::VAO;
unsigned int ShootingStar::VBO;
Shader * ShootingStar::shootingStarShader = nullptr;

ShootingStar::ShootingStar()
{
	transform->scale = glm::vec3(0.5f, 0.5f, 0.5f);

	//use a mersenne twister random number generation system to create some random velocities and spawns
	static std::mt19937 twister(glfwGetTime());
	static std::uniform_real_distribution<double> distr(-1, 1);

	//spawn every star at a random point on a sphere of radius 90 centered on 0,0
	transform->position = glm::vec3(distr(twister), distr(twister), distr(twister));
	transform->position = glm::normalize(transform->position);
	transform->position *= 90.f;

	//have every star target a point directly opposite it on the sphere
	glm::vec3 target = transform->position;
	target = -target; 

	//move the target position a little to avoid the stars flying straight through the island 
	glm::vec3 absTarget = glm::vec3(abs(target.x), abs(target.y), abs(target.z));
	if (absTarget.x >= absTarget.y && absTarget.x >= absTarget.z) {
		target.z += 80;
	}
	else if (absTarget.y >= absTarget.x && absTarget.y >= absTarget.z) {
		target.z += 80;
	}
	else if (absTarget.z >= absTarget.x && absTarget.z >= absTarget.y) {
		target.x += 80;
	}

	//set up velocity
	vel = target - transform->position;
	vel = glm::normalize(vel);
	vel *= 100.f; //increase speed	

	colour = glm::vec4(1.f, 1.f, 1.f, 1.f);
	//if we don't yet have a static shader, then we must make one (and Buffers) for all stars to use 
	if (shootingStarShader == nullptr) {
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
		shootingStarShader = ShaderCompiler::CreateProgram("SimpleVertexShader.glsl", "SimpleFragmentShader.glsl");
		Engine::GetEngineInstance()->mainCamera->OnWindowResize();
	}

	index = numPointLights++;

	stringstream stream;
	stream << "pointLights[" << index << "]";
	indexedPointLightArrayName = stream.str();

	//set up light source
	//Specify the type of light we are
	type = LightType::POINT;

	//attenutation values
	constant = 1.0f;
	linear = 0.027f;
	quadratic = 0.0028f;

	//colour values
	ambient = glm::vec3(0.001f, 0.001f, 0.001f);
	diffuse = glm::vec3(0.6f, 0.6f, 0.6f);
	specular = glm::vec3(1.0f, 1.0f, 1.0f);

	//get the shader and update it
	Shader * defaultShader = Engine::GetDefaultShaderProgram();
	UpdateShader(index, *defaultShader);
	defaultShader->SetInt("numPointLights", numPointLights);
	cout << "This star's index: " << index << endl;

	//set up trail
	trail = vector<glm::vec4>();
}

ShootingStar::~ShootingStar()
{
	numPointLights--;
}

void ShootingStar::Update(const float& deltaTime) {
	transform->position += vel * deltaTime;
	timeAlive += deltaTime;
	UpdateShader(index, *registeredShader);
	//add trail points
	if (Engine::Rand() % 10 <= 2) {
		trail.push_back(glm::vec4(transform->position, trailPointLifeSpan));
	}
	//remove trail points
	for (int i = trail.size() - 1; i >= 0; i--) {
		trail[i].w -= deltaTime;
		if (trail[i].w <= 0) {
			trail.erase(trail.begin() + i);
		}
	}
}

void ShootingStar::Display(glm::mat4 model) {
	//use the shader 
	shootingStarShader->Use();
	//set the colour
	shootingStarShader->SetVec4("colour", colour);
	//calculate a model matrix based on the parent model matrix 
	shootingStarShader->SetMat4("model", transform->ApplyToMatrix(model));
	//draw a cube 
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	for (glm::vec4 point : trail) {
		glm::mat4 pointModel = glm::mat4(1);
		pointModel = glm::translate(pointModel, glm::vec3(point.x, point.y, point.z));
		pointModel = glm::scale(pointModel, glm::vec3(1 * (point.w / trailPointLifeSpan)));
		pointModel = glm::scale(pointModel, glm::vec3(0.5f));
		shootingStarShader->SetMat4("model", pointModel);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void ShootingStar::UpdateShader(int _index, Shader& s) {
	//update the passed in shader to reflect our light data
	s.Use();
	index = _index;

	registeredShader = &s;

	s.SetVec3(indexedPointLightArrayName + ".ambient", ambient);
	s.SetVec3(indexedPointLightArrayName + ".diffuse", diffuse);
	s.SetVec3(indexedPointLightArrayName + ".specular", specular);
	s.SetFloat(indexedPointLightArrayName + ".constant", constant);
	s.SetFloat(indexedPointLightArrayName + ".linear", linear);
	s.SetFloat(indexedPointLightArrayName + ".quadratic", quadratic);
	s.SetVec3(indexedPointLightArrayName + ".position", transform->position);
}

bool ShootingStar::Finished() {
	return timeAlive > lifeSpan;
}