#pragma once
#include <glm/glm.hpp>
//class containing position, orientation and scale information
class Transform
{
public:
	glm::vec3 position;
	glm::vec3 orientation;
	glm::vec3 scale;

	Transform * parent = nullptr;

	Transform();
	~Transform();

	glm::mat4 ApplyToMatrix(glm::mat4 target);
};