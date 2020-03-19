#include "Mesh.h"
#include <glad/glad.h>
#include "MeshRenderer.h"
#include "Material.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Engine.h"
#include "Shader.h"

Mesh::Mesh(MeshRenderer * _mRenderer) : mRenderer(_mRenderer)
{
	//initialisation
	indices = vector<GLuint>();
}

Mesh::~Mesh()
{
}

void Mesh::InitBuffers() {
	//initialise the buffers needed in the GPU's memory
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, mRenderer->GetVertexBufferPointer());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
		&indices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}

void Mesh::AddIndex(unsigned int index) {
	//adds an index to the indices list
	indices.push_back(index);
}

void Mesh::Display(glm::mat4 model) {
	//displays this mesh based on the parent model matrix
	//use the material
	mMaterial->Use();
	Engine::GetDefaultShaderProgram()->SetMat4("model", transform->ApplyToMatrix(model));
	//display it 
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}