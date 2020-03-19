#pragma once

#include "Parser.h"

#include <string>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

class Face;
class MeshRenderer;
class Mesh;

//Static class to parse OBJ files
class ObjectParser : Parser
{
	static const char COMMENT_INDICATOR;
	static const string FACE_INDICATOR;
	static const string VERTEX_INDICATOR;
	static const string NORMAL_INDICATOR;
	static const string TEXTURE_VERTEX_INDICATOR;

	static const string MATERIAL_LIBRARY_INDICATOR;
	static const string USE_MATERIAL_INDICATOR;

	static const string NEW_GROUP_INDICATOR;
	static const string NEW_OBJECT_INDICATOR;

	static vector<vec3> positions;
	static vector<vec3> normals;
	static vector<vec2> textureCoordinates;
	static unsigned int vertexCount;

	static void ParseFace(stringstream& line, MeshRenderer * model, Mesh * mesh);
public:
	//methods
	static MeshRenderer * ParseFile(const string& fileName);
	static MeshRenderer * ParseFile(const string& fileName, const string& texFileName);

};