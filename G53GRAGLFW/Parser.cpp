#include "Parser.h"

Parser::Parser()
{
}

Parser::~Parser()
{
}

//parse a vector from a line 
glm::vec3 Parser::ParseVector(stringstream& line) {
	float x, y, z;
	line >> x >> y >> z;
	return glm::vec3(x, y, z);
}

//parse a 2D vector from a line 
glm::vec2 Parser::ParseTexVertex(stringstream& line) {
	float x, y;
	line >> x >> y;
	return glm::vec2(x, y);
}