#pragma once
#include "DisplayableObject.h"
#include <glm/glm.hpp>

class MeshRenderer;
//a small tree, really doesn't need to be its own class, but oh well
class SmallTree :
	public DisplayableObject
{
	static MeshRenderer * meshRenderer;
public:
	SmallTree();
	~SmallTree();
	void Display(glm::mat4 model);
};