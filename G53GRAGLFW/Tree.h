#pragma once
#include "DisplayableObject.h"
#include <glm/glm.hpp>

class MeshRenderer;
//It's a tree
class Tree :
	public DisplayableObject
{
	static MeshRenderer * meshRenderer;
public:
	Tree();
	~Tree();
	void Display(glm::mat4 model);
};