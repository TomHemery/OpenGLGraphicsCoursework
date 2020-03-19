#include "Tree.h"
#include "MeshRenderer.h"
#include "ObjectParser.h"
#include "Texture.h"
#include "Transform.h"

MeshRenderer * Tree::meshRenderer = nullptr;

Tree::Tree()
{
	//Yup, it's a tree
	transform->position = glm::vec3(4.f, -2.5f, 0.f);
	if(meshRenderer == nullptr)
		meshRenderer = ObjectParser::ParseFile("tree.obj");

	transform->scale = glm::vec3(10.f, 10.f, 10.f);
}

Tree::~Tree()
{

}

void Tree::Display(glm::mat4 model) {
	meshRenderer->Display(transform->ApplyToMatrix(model));
}