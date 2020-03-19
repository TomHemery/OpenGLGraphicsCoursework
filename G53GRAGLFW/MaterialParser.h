#pragma once
#include <string>
#include "Parser.h"

using namespace std;

class MaterialLibrary;

//Static Class to parse a material file (.mtl) used by the object parser
class MaterialParser : public Parser
{
	static const string NEW_MATERIAL_INDICATOR;

	static const string AMBIENT_COLOUR_INDICATOR;
	static const string DIFFUSE_COLOUR_INDICATOR;
	static const string SPECULAR_COLOUR_INDICATOR;
	static const string SPECULAR_EXPONENT_INDICATOR;

	static const string DIFFUSE_TEXTURE_MAP_INDICATOR;
	static const string SPECULAR_TEXTURE_MAP_INDICATOR;

public:
	//Methods
	static MaterialLibrary * ParseMaterialLibrary(const string& filename);
};

