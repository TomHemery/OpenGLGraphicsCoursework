#include "Engine.h"
#include "ShaderCompiler.h"
#include "Animatable.h"
#include "Shader.h"
#include "Camera.h"
#include "Lantern.h"
#include "Plane.h"
#include "ColourOperations.h"
#include "Tree.h"
#include "SmallTree.h"
#include "Skybox.h"
#include "Bird.h"
#include "Hill.h"
#include "OrbitingIsland.h"
#include "ShootingStarHandler.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>

//initialisation 
int Engine::windowHeight = 600;
int Engine::windowWidth = 800;

ShootingStarHandler * Engine::starHandler = nullptr;

Engine * Engine::Instance = nullptr;
Shader * Engine::defaultShaderProgram = nullptr;
vector<Shader *> Engine::allShaders = vector<Shader *>();
bool Engine::firstUpdate = true;

const double Engine::PI = 3.14159265359;

Engine::Engine() {
	//create the singleton reference 
	Instance = this;
}

Engine::~Engine() {
	//clean up 
	for (DisplayableObject * obj : displayableObjects) {
		delete obj;
	}
	for (Shader * shader : allShaders) {
		delete shader;
	}
	delete mainCamera;
}

void Engine::Run() {
	//run the thing 

	//initialise GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//create a window 
	window = glfwCreateWindow(windowWidth, windowHeight, "LanternScene", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	//initialise GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return;
	}
	glViewport(0, 0, windowWidth, windowHeight);

	glfwSetFramebufferSizeCallback(window, ResizeCallback);

	srand(time(NULL));

	//create the default shader program used for all lit objects in the scene 
	defaultShaderProgram = ShaderCompiler::CreateProgram("VertexShaderLighting.glsl", "FragmentShaderMultiLight.glsl");
	//set some information in the shader (call use before calling set)
	defaultShaderProgram->Use();
	defaultShaderProgram->SetInt("material.diffuse", 0);
	defaultShaderProgram->SetInt("material.specular", 1);

	//set up the callbacks for input through GLFW
	glfwSetCursorPosCallback(window, MouseMotionCallBack);
	glfwSetKeyCallback(window, KeyCallBack);
	glfwSetMouseButtonCallback(window, MouseButtonCallBack);

	//initialise scene objects 
	InitialiseScene();

	//main loop
	while (!glfwWindowShouldClose(window))
	{
		MainRenderLoop();
		glfwSwapBuffers(window);
		glfwPollEvents();
		CheckGLErrors();
	}

	//quit 
	glfwTerminate();
}

void Engine::InitialiseScene() {
	//set up the scene 

	//enable depth test, set a clear colour, disable the cursor 
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Create lanterns 
	Lantern * currentLantern = new Lantern(0.f, -1.6f, 0.f);
	currentLantern->transform->orientation = glm::vec3(-0.125f, 0.f, 0.f);
	displayableObjects.push_back(currentLantern);

	currentLantern = new Lantern(-.5f, -1.7f, 18.f);
	currentLantern->transform->orientation = glm::vec3(0.f, 0.f, 0.125f);
	displayableObjects.push_back(currentLantern);

	currentLantern = new Lantern(19.5f, -4.7f, 10.f);
	currentLantern->transform->orientation = glm::vec3(-0.125f, 0.f, -0.6f);
	displayableObjects.push_back(currentLantern);

	currentLantern = new Lantern(18.f, -7.6f, -15.f);
	currentLantern->transform->orientation = glm::vec3(-0.125f, 0.f, 0.f);
	displayableObjects.push_back(currentLantern);

	currentLantern = new Lantern(-2.f, -6.1f, -16.9f);
	currentLantern->transform->orientation = glm::vec3(-0.55f, 0.f, 0.1f);
	displayableObjects.push_back(currentLantern);

	currentLantern = new Lantern(-15.5f, -3.0f, 0.f);
	currentLantern->transform->orientation = glm::vec3(0.125f, 0.f, 0.f);
	displayableObjects.push_back(currentLantern);

	currentLantern = new Lantern(-14.f, -7.6f, -16.9f);
	currentLantern->transform->orientation = glm::vec3(-0.55f, 0.f, 0.1f);
	displayableObjects.push_back(currentLantern);

	currentLantern = new Lantern(26.5, -6.9, -0.2);
	currentLantern->transform->orientation = glm::vec3(0, PI / 2, 0);
	displayableObjects.push_back(currentLantern);
	currentLantern->SetColour(1.0f, 0.2f, 0.2f);

	//Create tree 
	displayableObjects.push_back(new Tree());

	//Create small tree
	SmallTree * smallTree = new SmallTree();
	smallTree->transform->position = glm::vec3(20, -8, 0);
	smallTree->transform->orientation = glm::vec3(0, 0, -PI / 4);
	displayableObjects.push_back(smallTree);

	//Create hill (rock really but I thought it was going to be a hill at one point)
	displayableObjects.push_back(new Hill());

	//Create bird
	Bird * mBird = new Bird();
	mBird->transform->position = glm::vec3(-0.3, 3.65, -0.7);
	mBird->transform->orientation = glm::vec3(0, 1.5, 0);
	displayableObjects.push_back(mBird);

	//a nice orbiting island to add some more motion to the scene 
	displayableObjects.push_back(new OrbitingIsland());

	//create a handler for the shooting stars, add it to the displayable objects list to get everything shown
	starHandler = new ShootingStarHandler();
	displayableObjects.push_back(starHandler);

	//Set up some shader information about directional light 
	Shader& defaultShader = *GetDefaultShaderProgram();
	defaultShader.Use();
	defaultShader.SetVec3("dirLight.direction", 0.f, -1.0f, 0.f);
	defaultShader.SetVec3("dirLight.ambient", 0.04f, 0.04f, 0.04f);
	defaultShader.SetVec3("dirLight.diffuse", 0.08f, 0.1f, 0.3f);
	defaultShader.SetVec3("dirLight.specular", 0.15f, 0.35f, 0.7f);

	//as a last step create the camera and the skybox - this should always be done last
	displayableObjects.push_back(new Skybox("custom"));
	mainCamera = new Camera();
}

void Engine::MainRenderLoop() {
	//work out time deltas 
	float currentTime = static_cast<float>(glfwGetTime());
	deltaTime = currentTime - lastFrame;
	lastFrame = currentTime;

	//use a flag to stop the first frame assuming that a massive time delta has happened
	if (firstUpdate) { 
		deltaTime = 0;
		firstUpdate = false;
	}
	
	//update the camera
	mainCamera->Update(deltaTime);

	//update any animatable objects
	for (DisplayableObject * obj : displayableObjects) {
		if (dynamic_cast<Animatable*>(obj) != nullptr) {
			dynamic_cast<Animatable*>(obj)->Update(deltaTime);
		}
	}

	//clear the screen and draw everything 
	glm::mat4 model = glm::mat4(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (DisplayableObject * obj : displayableObjects) {
		obj->Display(model);
	}
}

//checks for silent OPENGL errors 
int Engine::CheckGLErrors() {
	int e = 0;
	GLenum error = glGetError();
	while (GL_NO_ERROR != error)
	{
		++e;
		cout << "GL Error #" << e << ": " << error << endl;
		cout << glad_glGetError << endl;
		error = glGetError();
	}
	return e;
}

//returns a random number - this doesn't actually get used, oops
int Engine::Rand() {
	return rand();
}

//Mouse motion call back function 
void Engine::MouseMotionCallBack(GLFWwindow* window, double xpos, double ypos) {
	Instance->mainCamera->OnMouseMove(static_cast<float>(xpos), static_cast<float>(ypos));
}

//Mouse button call back function
void Engine::MouseButtonCallBack(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		starHandler->AddStar();
	}
}

//Key call back function 
void Engine::KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (action == GLFW_PRESS) {
		Instance->mainCamera->OnKeyDown(key, mods);
	}
	else if (action == GLFW_RELEASE) {
		Instance->mainCamera->OnKeyUp(key, mods);
	}
}

//Adds an object to the scene... also not used... oops 
void Engine::AddObjectToScene(DisplayableObject * obj) {
	displayableObjects.push_back(obj);
}

//Registers a shader by adding it to the list, so that camera updates are applied to it 
void Engine::RegisterShader(Shader * shader) {
	allShaders.push_back(shader);
}

//Resize call back 
void Engine::ResizeCallback(GLFWwindow* window, int width, int height)
{
	windowWidth = width;
	windowHeight = height;
	glViewport(0, 0, width, height);
	Instance->mainCamera->OnWindowResize();
}

//returns the window aspect (w / h)
float Engine::GetWindowAspect() {
	return static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
}