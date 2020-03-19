#include "ShootingStarHandler.h"
#include "ShootingStar.h"
#include <iostream>

ShootingStarHandler::ShootingStarHandler()
{
	stars = vector<ShootingStar *>();
}

ShootingStarHandler::~ShootingStarHandler()
{
}

void ShootingStarHandler::Update(const float& deltaTime) {
	ShootingStar * curr;
	for (int i = stars.size() - 1; i >= 0; i--) {
		curr = stars[i];
		curr->Update(deltaTime);
		if (curr->Finished()) {
			stars.erase(stars.begin() + i);
			delete curr;
		}
	}
}

void ShootingStarHandler::Display(glm::mat4 model) {
	model = transform->ApplyToMatrix(model);
	for (ShootingStar * curr : stars) {
		curr->Display(model);
	}
}

void ShootingStarHandler::AddStar() {
	if(stars.size() < maxStars) stars.push_back(new ShootingStar());
}