#pragma once
#include "Animatable.h"

class Hill;
class SmallTree;
class Lantern;

class OrbitingIsland :
	public Animatable
{
	Hill * mBase;
	SmallTree * mTree;
	Lantern * mLantern;
	float orbitAngle = 0.0f;
	float orbitSpeedBase = 0.4f;

	float rotationAngle = 0.0f;
	float rotationSpeedBase = 0.3f;

public:
	OrbitingIsland();
	~OrbitingIsland();
	void Update(const float& deltaTime);
	void Display(glm::mat4 model);
};

