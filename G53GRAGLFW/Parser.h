#pragma once
#include <glm/glm.hpp>
#include <sstream>

using namespace std;

//Base class for all parsers, can parse 2D and 3D vectors
class Parser
{
protected:
	static glm::vec3 ParseVector(stringstream& line);
	static glm::vec2 ParseTexVertex(stringstream& line);
public:
	Parser();
	~Parser();
};

