#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//class to simulate a Camera for the scene 
class Camera
{
	//various vectors representing important loction information 
	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::vec3 cameraDirection;
	glm::vec3 up;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;
	glm::mat4 view;
	glm::mat4 projection;
	//flags to keep track of where the camera should be moving 
					   //f		b	   l      r
	bool movement[4] = { false, false, false, false };

	//where the mouse was last recorded as being 
	float lastX = 0, lastY = 0;
	//yaw and pitch
	float yaw, pitch;
	//wether this is the first mouse input we have ever received (to stop the camera from jumping wildly at the start of the scene)
	bool firstMouseInput = true;
	//private method to reset everything about the camera to starting values 
	void Reset();

public:
	//constructors 
	Camera();
	~Camera();
	//methods
	void Update(float deltaTime);
	//events
	void OnWindowResize();
	void OnKeyDown(int key, int mods);
	void OnKeyUp(int key, int mods);
	void OnMouseMove(float mouseX, float mouseY);
	//getters 
	const glm::mat4& GetViewMatrix();
	const glm::mat4& GetProjectionMatrix();
};

