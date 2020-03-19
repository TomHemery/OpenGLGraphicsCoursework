#include "Camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Engine.h"
#include "Shader.h"
#include <iostream>

Camera::Camera()
{
	//assume that the mouse starts in the center of the screen 
	lastX = static_cast<float>(Engine::GetWindowWidth() / 2);
	lastY = static_cast<float>(Engine::GetWindowHeight() / 2);
	//reset everything
	Reset();
}

Camera::~Camera()
{
}

//resets camera and sets projection matrices for all shaders
void Camera::Reset() { 
	//a whole bunch of vector maths to simulate the camera's view frustrum
	cameraPos = glm::vec3(0.f, 0.f, 3.f);
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraDirection = glm::normalize(cameraTarget - cameraPos);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	cameraUp = glm::cross(cameraDirection, cameraRight);
	view = glm::lookAt(cameraPos, cameraTarget, up);
	yaw = -90.f;
	pitch = 0;
	//set up the frustrum within a projection matrix
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), Engine::GetWindowAspect(), 0.1f, 5000.0f);
	//loops through all shaders (automatically stored by engine) and sets their projection matrices
	for (Shader * shader : Engine::GetAllRegisteredShaders()){
		shader->Use();
		shader->SetMat4("projection", projection);
	}
}

//called once per frame as a special case (there is only one camera in the scene ever)
void Camera::Update(float deltaTime) {
	//handle motion - there might be a prettier way to do this I'm not sure 
	glm::vec3 movementVec(0, 0, 0);

	if (movement[0]) movementVec += cameraDirection;
	if (movement[1]) movementVec -= cameraDirection;
	if (movement[2]) movementVec -= glm::normalize(glm::cross(cameraDirection, cameraUp));
	if (movement[3]) movementVec += glm::normalize(glm::cross(cameraDirection, cameraUp));
	
	if(movementVec.x > 0 || movementVec.y > 0 || movementVec.z > 0)
		movementVec = glm::normalize(movementVec);

	cameraPos += movementVec * 10.f * deltaTime;

	//set up the view matrix and the view position in all shaders
	view = glm::mat4(1.0f); 
	view = glm::lookAt(cameraPos, cameraPos + cameraDirection, cameraUp);
	for (Shader * shader : Engine::GetAllRegisteredShaders()) {
		shader->Use();
		shader->SetMat4("view", view);
		shader->SetVec3("viewPos", cameraPos);
	}
	void HandleKey(int key, int scancode, int action, int mods);
}

//update the projection whenever the window resizes 
void Camera::OnWindowResize() {
	projection = glm::perspective(glm::radians(60.0f), Engine::GetWindowAspect(), 0.1f, 5000.0f);
	for (Shader * shader : Engine::GetAllRegisteredShaders()) {
		shader->Use();
		shader->SetMat4("projection", projection);
	}
}

//handle key inputs
void Camera::OnKeyDown(int key, int mods) {
	switch (key) {
	case GLFW_KEY_W:
		movement[0] = true;
		break;
	case GLFW_KEY_A:
		movement[2] = true;
		break;
	case GLFW_KEY_S:
		movement[1] = true;
		break;
	case GLFW_KEY_D:
		movement[3] = true;
		break;
	case GLFW_KEY_SPACE:
		Reset();
		break;
	}
}

//handle key inputs
void Camera::OnKeyUp(int key, int mods) {
	switch (key) {
	case GLFW_KEY_W:
		movement[0] = false;
		break;
	case GLFW_KEY_A:
		movement[2] = false;
		break;
	case GLFW_KEY_S:
		movement[1] = false;
		break;
	case GLFW_KEY_D:
		movement[3] = false;
		break;
	}
}

//handle mouse motion
void Camera::OnMouseMove(float mouseX, float mouseY) {
	if (firstMouseInput) {
		lastX = mouseX;
		lastY = mouseY;
		firstMouseInput = false;
	}
	else {
		float xoffset = mouseX - lastX;
		float yoffset = lastY - mouseY;
		lastX = mouseX;
		lastY = mouseY;

		float sensitivity = 0.05f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		pitch = pitch > 89.0f ? 89.0f : pitch;
		pitch = pitch < -89.0f ? -89.0f : pitch;

		glm::vec3 front;
		front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		front.y = sin(glm::radians(pitch));
		front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
		cameraDirection = glm::normalize(front);
	}
}

//get a const reference to the view matrix
const glm::mat4& Camera::GetViewMatrix() {
	return view;
}

//get a const reference to the projection matrix
const glm::mat4& Camera::GetProjectionMatrix() {
	return projection;
}