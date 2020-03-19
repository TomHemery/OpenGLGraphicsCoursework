#include "MaterialLibrary.h"
#include "Material.h"

MaterialLibrary::MaterialLibrary()
{
}

MaterialLibrary::~MaterialLibrary()
{
	//clean up
	for (auto m : materials) { //delete all materials
		delete m.second;
	}
}

//add a material with a given key
void MaterialLibrary::AddMaterial(const string& key, Material * m) {
	materials[key] = m;
}

//retrieve a material with a given key
Material * MaterialLibrary::GetMaterial(const string& key) {
	return materials[key];
}