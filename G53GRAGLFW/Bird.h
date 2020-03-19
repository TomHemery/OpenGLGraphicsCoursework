#pragma once
#include "Animatable.h"
//forward declarations 
class MeshRenderer;
class Mesh;
//Bird class - animatable representation of the bird from the scene 
class Bird :
	public Animatable
{
	//private rendering objects 
	MeshRenderer * mRenderer;
	Mesh * leftWing;
	Mesh * rightWing;
	Mesh * head;
public:
	Bird();
	~Bird();
	void Display(glm::mat4 model);
	void Update(const float& deltaTime);
};