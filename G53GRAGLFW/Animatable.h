#pragma once
#include "DisplayableObject.h"
//Interface class for animatable objects to extend 
class Animatable : public DisplayableObject
{
public:
	Animatable() {}
	//Destructor is virtual to ensure that the correct destructor is called on object deletion 
	virtual ~Animatable(void) {}
	//Update method - called once per frame with a time delta in seconds passed in 
	virtual void Update(const float& deltaTime) = 0;
};