#include "MaterialParser.h"
#include "MaterialLibrary.h"
#include "Material.h"
#include "Texture.h"
#include <fstream>
#include <sstream>
#include <iostream>

//Initialisation
const string MaterialParser::NEW_MATERIAL_INDICATOR = "newmtl";

const string MaterialParser::AMBIENT_COLOUR_INDICATOR = "Ka";
const string MaterialParser::DIFFUSE_COLOUR_INDICATOR = "Kd";
const string MaterialParser::SPECULAR_COLOUR_INDICATOR = "Ks";
const string MaterialParser::SPECULAR_EXPONENT_INDICATOR = "Ns"; 

const string MaterialParser::DIFFUSE_TEXTURE_MAP_INDICATOR = "map_Kd";
const string MaterialParser::SPECULAR_TEXTURE_MAP_INDICATOR = "map_Ks";

MaterialLibrary * MaterialParser::ParseMaterialLibrary(const string& filename) {
	//work out the path to the material
	string path = "../Materials/" + filename;
	//open it 
	ifstream fileStream(path, ios_base::in);

	if (!fileStream) { // error
		cerr << "MTL Library " << filename << " not found in " << path << endl;
		return nullptr;
	}
	else { //success
		cout << "Found MTL Library " << filename << " in " << path << endl;
	}

	//create a material library 
	MaterialLibrary * resultMaterialLibrary = new MaterialLibrary();
	Material * currentMaterial = nullptr;
	string line;

	//go through mtl file line by line looking for information
	while (getline(fileStream, line)) {
		if (line.length() > 0) { //if this isn't just a blank line 
			//extract first word using the magic of string streams
			stringstream lineStream(line);
			string firstWord;
			lineStream >> firstWord;
			//if we find a new material indicator, create a new material in the library
			if (firstWord == NEW_MATERIAL_INDICATOR) {
				string materialName;
				lineStream >> materialName;
				if (currentMaterial != nullptr)
					resultMaterialLibrary->AddMaterial(currentMaterial->GetName(), currentMaterial);
				currentMaterial = new Material(materialName);
			}
			//otherwise, if we haven't yet created a material then we have an issue
			else if (currentMaterial == nullptr) {
				cout << "Error, material information specified without first creating a material" << endl;
				fileStream.close();
				delete resultMaterialLibrary;
				return nullptr;
			}
			//read the file (fairly self explanatory)
			else {
				if (firstWord == AMBIENT_COLOUR_INDICATOR) {
					currentMaterial->SetAmbientColour(ParseVector(lineStream));
				}
				else if (firstWord == DIFFUSE_COLOUR_INDICATOR) {
					currentMaterial->SetDiffuseColour(ParseVector(lineStream));
				}
				else if (firstWord == SPECULAR_COLOUR_INDICATOR) {
					currentMaterial->SetSpecularColor(ParseVector(lineStream));
				}
				else if (firstWord == SPECULAR_EXPONENT_INDICATOR) {
					float shininess;
					lineStream >> shininess;
					currentMaterial->SetShininess(shininess);
				}
				else if (firstWord == DIFFUSE_TEXTURE_MAP_INDICATOR) {
					string filename;
					lineStream >> filename;
					currentMaterial->SetDiffuseMap(new Texture(filename));
				}
				else if (firstWord == SPECULAR_TEXTURE_MAP_INDICATOR) {
					string filename;
					lineStream >> filename;
					currentMaterial->SetSpecularMap(new Texture(filename));
				}
			}
		}
	}

	//put the last created material in the library
	if (currentMaterial != nullptr)
		resultMaterialLibrary->AddMaterial(currentMaterial->GetName(), currentMaterial);

	//close the file
	fileStream.close();

	//yay
	cout << "Created material library: " << filename << endl;

	return resultMaterialLibrary;
}