#include "SmallTree.h"
#include "MeshRenderer.h"
#include "ObjectParser.h"
#include "Texture.h"
#include "Transform.h"

MeshRenderer * SmallTree::meshRenderer = nullptr;

SmallTree::SmallTree()
{
	//yup (just don't do it multiple times
	if(meshRenderer == nullptr)
		meshRenderer = ObjectParser::ParseFile("TreeSmall.obj");
	//yup
	transform->scale = glm::vec3(5.f, 5.f, 5.f);
}

SmallTree::~SmallTree()
{

}
//show it
void SmallTree::Display(glm::mat4 model) {
	meshRenderer->Display(transform->ApplyToMatrix(model));
}