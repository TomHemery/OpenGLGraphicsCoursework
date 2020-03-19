#include "EmberSystem.h"
#include "Ember.h"
#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

EmberSystem::EmberSystem()
{
	//set up ember storage, create a new transform
	embers = vector<Ember *>();
	//move our location so that we are in the right position in the lantern model (it's not quite centered at 0, 0 annoyingly)
	transform->position = glm::vec3(-3.f, 8.f, 2.f);
	//set an initial start colour 
	emberStartColour = glm::vec4(1.f, 1.f, 1.f, 1.f);
	//create a new ember to allow the ember class to set up it's shaders and stuff... doesn't really NEED to happen here 
	embers.push_back(new Ember(emberStartColour));
}

EmberSystem::~EmberSystem()
{
}

void EmberSystem::Display(glm::mat4 model) {
	//create a model matrix based on our transform
	model = transform->ApplyToMatrix(model);
	
	//show all embers based on the model matrix
	for (Ember * e : embers) {
		e->Display(model);
	}
}

void EmberSystem::Update(const float& deltaTime) {
	//update all embers, create and delete as necessary 
	Ember * e;
	timeSinceLastSpawn += deltaTime;
	if (timeSinceLastSpawn > maxTimeBetweenSpawns) {
		embers.push_back(new Ember(emberStartColour));
		timeSinceLastSpawn = 0.f;
	}
	for (int i = embers.size() - 1; i >= 0; i--) {
		e = embers[i];
		e->Update(deltaTime);
		if (e->Finished()) {
			embers.erase(embers.begin() + i);
			delete e;
		}
	}
}