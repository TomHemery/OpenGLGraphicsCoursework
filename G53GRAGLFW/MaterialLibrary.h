#pragma once

#include <unordered_map>
#include <string>

using namespace std;

class Material;

//class for a material library, created when loading objects and holds multiple materials 
class MaterialLibrary
{
	//unordered hash map of materials 
	unordered_map<string, Material *> materials;
public:
	//constructors 
	MaterialLibrary();
	~MaterialLibrary();
	//mutators
	void AddMaterial(const string& key, Material * m);
	//getters
	Material * GetMaterial(const string& key);
};