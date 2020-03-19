#include "Plane.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Engine.h"
#include "Shader.h"
#include "Texture.h"
//LEGACY class - has some standard stuff to draw a textured plane in GL
vector<float> Plane::vertices = {
		 0.5f, 0.f,  0.5f, 		0.0f,  1.0f, 0.0f,		1.0f, 1.0f,
		 0.5f, 0.f, -0.5f,		0.0f,  1.0f, 0.0f,		1.0f, 0.0f,
		-0.5f, 0.f, -0.5f, 		0.0f,  1.0f, 0.0f,		0.0f, 0.0f,
		-0.5f, 0.f, -0.5f, 		0.0f,  1.0f, 0.0f,		0.0f, 0.0f,
		-0.5f, 0.f,  0.5f,		0.0f,  1.0f, 0.0f,		0.0f, 1.0f,
		 0.5f, 0.f,  0.5f, 		0.0f,  1.0f, 0.0f,		1.0f, 1.0f
};

unsigned int Plane::VAO = 0;
unsigned int Plane::VBO = 0;
bool Plane::LoadedTextureAndBuffers = false;
Texture * Plane::diffuse = nullptr;
Texture * Plane::specular = nullptr;

Plane::Plane(float x, float y, float z){
	if (!LoadedTextureAndBuffers) {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// normal attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// texture attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
		//unbind all
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		diffuse = new Texture("grass_diffuse.jpg");
		specular = new Texture("grass_specular.jpg");
		LoadedTextureAndBuffers = true;
	}	
	transform->position = glm::vec3(x, y, z);
	transform->scale = glm::vec3(20.f, 20.f, 20.f);
}

Plane::~Plane(){
}

void Plane::Display(glm::mat4 model) {
	Engine::GetDefaultShaderProgram()->Use();
	Engine::GetDefaultShaderProgram()->SetFloat("material.shininess", 32.0f);

	glActiveTexture(GL_TEXTURE0);
	diffuse->Use();
	glActiveTexture(GL_TEXTURE1);
	specular->Use();

	model = glm::translate(model, transform->position);
	model = glm::scale(model, transform->scale);
	Engine::GetDefaultShaderProgram()->SetMat4("model", model);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
}