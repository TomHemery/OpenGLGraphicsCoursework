#include "Bird.h"
#include "MeshRenderer.h"
#include "ObjectParser.h"
#include "Mesh.h"
#include <iostream>
#include "Engine.h"

Bird::Bird()
{
	//parse an obj file to create a MeshRenderer
	mRenderer = ObjectParser::ParseFile("Bird_Separated.obj");
	//set scale 
	transform->scale = glm::vec3(0.2, 0.2, 0.2);
	//locate the separate parts of the bird for animation
	leftWing = mRenderer->GetMeshByName("LeftWing");
	rightWing = mRenderer->GetMeshByName("RightWing");
	head = mRenderer->GetMeshByName("Head");
}

Bird::~Bird()
{
	//clean up
	delete mRenderer;
}

void Bird::Display(glm::mat4 model) {
	//show the meshrenderer using our current transform 
	mRenderer->Display(transform->ApplyToMatrix(model));
}

void Bird::Update(const float& deltaTime) {
	//use some sine maths to create a looping animation of the bird moving its wings / head
	float totalDelta = static_cast<float>(glfwGetTime());

	float wingSinVal = (sin(totalDelta * 4) + 1) / 3;
	float headSinVal = sin(totalDelta);

	leftWing->transform->orientation.y = -wingSinVal;
	leftWing->transform->position.z = wingSinVal;

	rightWing->transform->orientation.y = wingSinVal;
	rightWing->transform->position.z = -wingSinVal;

	head->transform->orientation.x = headSinVal / 4;
	head->transform->position.z = -headSinVal / 4 * 6;
}