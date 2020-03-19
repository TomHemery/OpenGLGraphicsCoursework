#pragma once
#include <vector>
#include "DisplayableObject.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Vertex.h"
#include "DisplayableObject.h"

#include <glm/glm.hpp>

using namespace std;

class Vector3;
class Shader;
class Texture;
class MaterialLibrary;
class Transform;
class Mesh;

//A collection of meshes that build one complete object renderer
class MeshRenderer : public DisplayableObject
{
	//materials 
	MaterialLibrary * mMaterials;
	//each object has one set of vertexes that are used between all meshes
	unsigned int VBO;
	vector<Vertex> vertices;
	//meshes
	vector<Mesh *> meshes;

public:
	//Constructors
	MeshRenderer();
	~MeshRenderer();
	//mutators
	void Init();
	void AddVertex(Vertex& newVertex);
	void AddMesh(Mesh * newMesh);
	//getters
	int GetVertexBufferPointer();
	//getters
	MaterialLibrary * GetMaterialLibrary();
	Mesh * GetMeshByName(string name);
	//setters
	void SetMaterialLibrary(MaterialLibrary * lib) { mMaterials = lib; }
	//overwriters
	void Display(glm::mat4 model);
};

