#pragma once
#include "Transform.h"
#include <glm/common.hpp>
//Interface class for displayable objects to extend
class DisplayableObject
{
public:
	//All displayable objects must have a transform - to specify location, scale and orientation 
	Transform * transform;
	//The constructor creates a new transform 
	DisplayableObject() : transform(new Transform()) {};
	virtual ~DisplayableObject(void) {};
	//All displayable objects have a display method called once a  frame 
	virtual void Display(glm::mat4 model) = 0;
};