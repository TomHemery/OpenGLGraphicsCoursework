#pragma once
#include "Animatable.h"
#include <vector>
using namespace std;

class ShootingStar;

class ShootingStarHandler :
	public Animatable
{
	vector <ShootingStar *> stars;
	int maxStars = 10;
public:
	//constructors
	ShootingStarHandler();
	~ShootingStarHandler();
	//methods
	void Update(const float& deltaTime);
	void Display(glm::mat4 model);
	//mutators
	void AddStar();
};

