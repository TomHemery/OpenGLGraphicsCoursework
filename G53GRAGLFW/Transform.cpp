#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

Transform::Transform()
{
	//yup
	scale = glm::vec3(1);
	position = glm::vec3(0);
	orientation = glm::vec3(0);
}

Transform::~Transform()
{
}

glm::mat4 Transform::ApplyToMatrix(glm::mat4 target) {
	
	target = glm::translate(target, position);
	target = glm::scale(target, scale);
	
	target = glm::rotate(target, orientation.x, glm::vec3(1, 0, 0));
	target = glm::rotate(target, orientation.y, glm::vec3(0, 1, 0));
	target = glm::rotate(target, orientation.z, glm::vec3(0, 0, 1));
	return target;
}