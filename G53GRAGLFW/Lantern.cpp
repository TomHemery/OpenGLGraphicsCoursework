#include "Lantern.h"
#include "MeshRenderer.h"
#include "ObjectParser.h"
#include "Texture.h"
#include "Shader.h"
#include "Engine.h"
#include "ShaderCompiler.h"
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>
#include "EmberSystem.h"

//Initialisation
MeshRenderer * Lantern::LanternModel = nullptr;

Lantern::Lantern(float x, float y, float z){
	//If we haven't loaded a model yet, do it (only gets done once throughout run time)
	if (LanternModel == nullptr) {
		LanternModel = ObjectParser::ParseFile("oil_lamp_no_glass.obj");
	}
	//Specify the type of light we are
	type = LightType::POINT;

	//attenutation values
	constant = 1.0f;
	linear = 0.027f;
	quadratic = 0.0028f;

	//set up transform 
	transform->position = glm::vec3(x, y, z);
	transform->scale = glm::vec3(0.1f, 0.1f, 0.1f);

	//get the shader and update it
	index = numPointLights++;
	stringstream stream;
	stream << "pointLights[" << index << "]";
	indexedPointLightArrayName = stream.str();
	Shader * defaultShader = Engine::GetDefaultShaderProgram();
	UpdateShader(index, *defaultShader);
	defaultShader->SetInt("numPointLights", numPointLights);

	//create a new ember system 
	mEmberSystem = new EmberSystem();

	//set our colour to a pleasing red
	SetColour(1.0f, 0.5f, 0.f);

	
}

Lantern::~Lantern(){
	//clean up
	delete mEmberSystem;
	delete transform;
}

void Lantern::Display(glm::mat4 model) {
	//calculate model matrix
	model = transform->ApplyToMatrix(model);

	//display the ember system using model matrix as parent model 
	mEmberSystem->Display(model);

	//draw the lantern with the regular scene lighting (it receives lighting information from all point lights in the scene)
	registeredShader->Use();

	glm::vec3 absPosition = model * glm::vec4(transform->position, 1);
	absPosition.y += lightSourceOffset;
	registeredShader->SetVec3(indexedPointLightArrayName + ".position", absPosition);

	LanternModel->Display(model);
}

void Lantern::Update(const float& deltaTime) {
	//update the attenuation over time to create a "flickering" effect
	float baseLinear = 0.014f;
	float baseQuadratic = 0.0007f;
	float sinVal = sin((index + glfwGetTime()) * 4) / 9 + 0.1f;
	linear = baseLinear + sinVal;
	baseQuadratic = baseQuadratic + sinVal / 10;
	UpdateShader(index, *registeredShader);
	//update the ember particle system
	mEmberSystem->Update(deltaTime);
}

void Lantern::UpdateShader(int _index, Shader& s) {
	//update the passed in shader to reflect our light data
	s.Use();
	index = _index;

	registeredShader = &s;

	s.SetVec3(indexedPointLightArrayName + ".ambient", ambient);
	s.SetVec3(indexedPointLightArrayName + ".diffuse", diffuse);
	s.SetVec3(indexedPointLightArrayName + ".specular", specular);
	s.SetFloat(indexedPointLightArrayName + ".constant", constant);
	s.SetFloat(indexedPointLightArrayName + ".linear", linear);
	s.SetFloat(indexedPointLightArrayName + ".quadratic", quadratic);
}

void Lantern::SetColour(float r, float g, float b) {
	//set the colour of the light 
	ambient = glm::vec3(0.001f * r, 0.001f * g, 0.001f * b);
	diffuse = glm::vec3(0.6f * r, 0.6f * g, 0.6f * b);
	specular = glm::vec3(1.0f * r, 1.0f * g, 1.0f * b);
	UpdateShader(index, *registeredShader);
	mEmberSystem->SetStartColour(glm::vec4(r < 0.2 ? 0.2 : r, g < 0.2 ? 0.2 : g, b < 0.2 ? 0.2 : b, 1));
} 