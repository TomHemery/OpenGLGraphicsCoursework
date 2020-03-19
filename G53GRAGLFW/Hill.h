#pragma once
#include "DisplayableObject.h"

class MeshRenderer;

//yeah this isn't actually a hill... it's a rock
class Hill : public DisplayableObject
{

	static MeshRenderer * mRenderer;

public:
	Hill();
	~Hill();
	void Display(glm::mat4 model);
};

