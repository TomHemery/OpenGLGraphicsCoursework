#pragma once
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include "Animatable.h"
using namespace std;
class Ember;
//Class to represent a particle system for embers being created by each lamp
class EmberSystem : public Animatable
{
	//used to hold ember pointers 
	vector<Ember *> embers;

	//spawn rate information 
	float timeSinceLastSpawn = 0.f;
	float maxTimeBetweenSpawns = 0.3f;

	//our position and some other information 
	glm::vec4 emberStartColour;

public:
	//Constructors
	EmberSystem();
	~EmberSystem();
	//Methods 
	void Update(const float& deltaTime);
	void Display(glm::mat4 model);
	//Setters
	void SetStartColour(glm::vec4 _startColour) { emberStartColour = _startColour; }
};

