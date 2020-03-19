#pragma once
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Vertex.h"
#include "DisplayableObject.h"

using namespace std;

class MeshRenderer;
class Material;
class Transform;

//represents one individual object loaded from an OBJ
class Mesh : public DisplayableObject
{
	//rendering and material
	MeshRenderer * mRenderer;
	Material * mMaterial;

	//buffers
	unsigned int VAO;
	unsigned int EBO;

	//indices (for EBO)
	vector<GLuint> indices;

	//A name
	string name;

public:

	//constructors
	Mesh(MeshRenderer * _mRenderer);
	~Mesh();
	//mutators
	void InitBuffers();
	void AddIndex(unsigned int index);
	//getters
	const string& GetName() { return name; }
	//setters
	void SetMaterial(Material * mat) { mMaterial = mat; };
	void SetName(string _name) { name = _name; }
	//methods
	void Display(glm::mat4 model);
};

