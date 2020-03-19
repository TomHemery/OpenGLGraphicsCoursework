#include "MeshRenderer.h"
#include "Engine.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "ShaderCompiler.h"
#include "Texture.h"
#include "Mesh.h"

MeshRenderer::MeshRenderer()
{
	//create a vector to store meshes
	meshes = vector<Mesh*>();
}

MeshRenderer::~MeshRenderer()
{
	//clean up
	for (Mesh * m : meshes) {
		delete m;
	}
}

void MeshRenderer::Init() {
	//create a vertex buffer object in GPU memory
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
		&vertices[0], GL_STATIC_DRAW);
	for (Mesh * m : meshes) {
		//initialise all buffers in meshes
		m->InitBuffers();
	}
}

void MeshRenderer::AddVertex(Vertex& newVertex) {
	//add a vertex
	vertices.push_back(newVertex);
}

void MeshRenderer::AddMesh(Mesh * newMesh) {
	//add a mesh
	meshes.push_back(newMesh);
}

int MeshRenderer::GetVertexBufferPointer() {
	//get the VBO
	return VBO;
}

MaterialLibrary * MeshRenderer::GetMaterialLibrary() {
	//get the materials library
	return mMaterials;
}

Mesh * MeshRenderer::GetMeshByName(string name) {
	//get a mesh by name (O(n))
	for (Mesh * m : meshes) {
		if (m->GetName() == name) {
			return m;
		}
	}
	return nullptr;
}

//Display the mesh renderer
void MeshRenderer::Display(glm::mat4 model) {
	Engine::GetDefaultShaderProgram()->SetMat4("model", model);
	//Display each mesh
	for (Mesh * m : meshes) {
		m->Display(model);
	}
}