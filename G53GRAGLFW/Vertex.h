#pragma once
#include <glm/glm.hpp>
//Handy dandy OpenGL friendly vertex struct to contain all sorts of nice information
struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};