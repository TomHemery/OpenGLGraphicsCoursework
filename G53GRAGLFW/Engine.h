#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class DisplayableObject;
class Shader;
class Camera;
class Light;
class ShootingStarHandler;

using namespace std;

//Singleton class to handle everything behind the scenes, including creating the window and calling display methods etc.
class Engine
{
	//Shader information 
	static Shader * defaultShaderProgram;
	static vector<Shader *> allShaders;
	//Displayable objects and light sources
	vector<DisplayableObject *> displayableObjects;
	vector<Light *> lights;
	static ShootingStarHandler * starHandler;

	//default projection matrix (pretty sure this doesn't need to be here any more)
	glm::mat4 projection = glm::mat4(1.0f);
	//a window pointer
	GLFWwindow * window;

	//time keeping
	float deltaTime = 0.0f;
	float lastFrame = 0.0f; 

	//flag the first update to prevent a massive amount of motion on the first frame 
	static bool firstUpdate;

protected:
	//width height, singleton 
	static int windowWidth;
	static int windowHeight;
	static Engine * Instance;
	
public:

	//a lot of stuff here is static to enable other classes easy access
	static const double PI;

	Camera * mainCamera;

	Engine();
	~Engine();
	//methods
	void InitialiseScene();
	void MainRenderLoop();
	static int CheckGLErrors();
	static int Rand();
	//mutators
	void Run();
	void AddObjectToScene(DisplayableObject * obj);
	static void RegisterShader(Shader * shader);
	//callbacks
	static void MouseMotionCallBack(GLFWwindow* window, double xpos, double ypos);
	static void MouseButtonCallBack(GLFWwindow* window, int button, int action, int mods);
	static void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void ResizeCallback(GLFWwindow* window, int width, int height);	
	//getters
	static int GetWindowWidth() { return windowWidth; }
	static int GetWindowHeight() { return windowHeight; }
	static float GetWindowAspect();
	static Shader * GetDefaultShaderProgram() { return defaultShaderProgram; }
	static const vector<Shader *> GetAllRegisteredShaders() { return allShaders; }
	static const Engine * GetEngineInstance() { return Instance; }
};