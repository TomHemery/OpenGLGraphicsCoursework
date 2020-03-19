#include "OrbitingIsland.h"
#include "Hill.h"
#include "SmallTree.h"
#include "Lantern.h"
#include <glm/gtc/matrix_transform.hpp>


OrbitingIsland::OrbitingIsland()
{
	mBase = new Hill();
	mBase->transform->scale = glm::vec3(4, 4, 4);

	mTree = new SmallTree();
	mTree->transform->scale = glm::vec3(4);
	mTree->transform->position = glm::vec3(0, -18, 0);

	mLantern = new Lantern(-3, -16.5f , 0);
	mLantern->SetColour(0.8f, 0.3f, 1.0f);

	transform->position = glm::vec3(40, 20, 0);
}


OrbitingIsland::~OrbitingIsland()
{
}

void OrbitingIsland::Update(const float& deltaTime) {
	orbitAngle = orbitAngle + orbitSpeedBase * deltaTime;
	rotationAngle = rotationAngle + rotationSpeedBase * deltaTime;
	transform->orientation.y = rotationAngle;
	transform->position.y = 20 + sin(2 * orbitAngle) * 8;
	mLantern->Update(deltaTime);
}

void OrbitingIsland::Display(glm::mat4 model) {
	model = glm::rotate(model, orbitAngle, glm::vec3(0, 1, 0));
	model = transform->ApplyToMatrix(model);
	mBase->Display(model);
	mTree->Display(model);
	mLantern->Display(model);
}