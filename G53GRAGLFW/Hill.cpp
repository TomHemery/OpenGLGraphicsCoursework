#include "Hill.h"
#include "MeshRenderer.h"
#include "ObjectParser.h"

MeshRenderer * Hill::mRenderer = nullptr;

Hill::Hill()
{
	//this loads a rock... because why not 
	//tbh this doesn't need to be its own class but it is, because it's nice to contain the transform information 
	if(mRenderer == nullptr) 
		mRenderer = ObjectParser::ParseFile("rock.obj");
	transform->position = glm::vec3(0, -20, 0);
	transform->scale = glm::vec3(20, 20, 20);
}


Hill::~Hill()
{
	delete mRenderer;
}

	 
void Hill::Display(glm::mat4 model) {
	mRenderer->Display(transform->ApplyToMatrix(model));
}