#include "ObjectParser.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "MaterialParser.h"
#include "MaterialLibrary.h"

#include <fstream>
#include <sstream>
#include <iostream>

const char ObjectParser::COMMENT_INDICATOR = '#';
const string ObjectParser::VERTEX_INDICATOR = "v";
const string ObjectParser::FACE_INDICATOR = "f";
const string ObjectParser::NORMAL_INDICATOR = "vn";
const string ObjectParser::TEXTURE_VERTEX_INDICATOR = "vt";

const string ObjectParser::MATERIAL_LIBRARY_INDICATOR = "mtllib";
const string ObjectParser::USE_MATERIAL_INDICATOR = "usemtl";

const string ObjectParser::NEW_GROUP_INDICATOR = "g";
const string ObjectParser::NEW_OBJECT_INDICATOR = "o";

vector<vec3> ObjectParser::positions = vector<vec3>();
vector<vec3> ObjectParser::normals = vector<vec3>();
vector<vec2> ObjectParser::textureCoordinates = vector<vec2>();
unsigned int ObjectParser::vertexCount = 0;

//Parse a file, the code has changed a lot, texFileName is left over from before materials were supported
MeshRenderer * ObjectParser::ParseFile(const string& objFileName) {
	return ParseFile(objFileName, "");
}

//Parse a file, texFileName does nothing
MeshRenderer * ObjectParser::ParseFile(const string& objFileName, const string& texFileName) {
	//find the path to the object
	string objPath = "../Models/" + objFileName;
	//create a file stream
	ifstream fileStream(objPath, ios_base::in);
	//if we didn't find it then error
	if (!fileStream) {
		cerr << "File " << objFileName << " not found in " << objPath << endl;
		return nullptr;
	}
	//yay
	else {
		cout << "Found file " << objFileName << " in " << objPath << endl;
	}

	//yup
	positions = vector<vec3>();
	normals = vector<vec3>();
	textureCoordinates = vector<vec2>();

	//yup
	vertexCount = 0;

	//yup
	string line;

	//ooh the returned model
	MeshRenderer * resultModel = new MeshRenderer();
	//the current mesh
	Mesh * currentMesh = nullptr;
	
	//line by line (literally tens of thousands of lines often)
	while (getline(fileStream, line)) {
		stringstream lineStream(line);
		string firstWord;
		lineStream >> firstWord;
		if (firstWord[0] != COMMENT_INDICATOR && line.length() > 0) { //valid line
			if (firstWord == VERTEX_INDICATOR) {//line is a vertex
				positions.push_back(ParseVector(lineStream));
			}
			else if (firstWord == NORMAL_INDICATOR) {//line is a normal
				normals.push_back(ParseVector(lineStream));
			}
			else if (firstWord == TEXTURE_VERTEX_INDICATOR) {//line is a tex vertex
				textureCoordinates.push_back(ParseTexVertex(lineStream));
			}
			else if (firstWord == FACE_INDICATOR) {//line is a face
				if (currentMesh == nullptr) {
					currentMesh = new Mesh(resultModel);
					resultModel->AddMesh(currentMesh);
				}
				ParseFace(lineStream, resultModel, currentMesh);
			}
			else if (firstWord == MATERIAL_LIBRARY_INDICATOR) {//a material library is referenced by this object
				string filename;
				lineStream >> filename;
				resultModel->SetMaterialLibrary(MaterialParser::ParseMaterialLibrary(filename));
			}
			// this represents a new group of vertices - i.e. a separate mesh
			else if (firstWord == NEW_GROUP_INDICATOR || firstWord == NEW_OBJECT_INDICATOR) {
				currentMesh = new Mesh(resultModel);
				string meshName;
				lineStream >> meshName;
				currentMesh->SetName(meshName);
				resultModel->AddMesh(currentMesh);
			}
			//this tells us to use a material when rendering the following faces
			else if (firstWord == USE_MATERIAL_INDICATOR) {
				if (currentMesh == nullptr) {
					currentMesh = new Mesh(resultModel);
					resultModel->AddMesh(currentMesh);
				}
				string matName;
				lineStream >> matName;
				Material * mat = resultModel->GetMaterialLibrary()->GetMaterial(matName);
				currentMesh->SetMaterial(mat);
			}
		}
	}

	//close it
	fileStream.close();

	resultModel->Init();
	cout << "Built Model Mesh: " << objFileName << endl;
	return resultModel;
}

//parse a face from a line 
void ObjectParser::ParseFace(stringstream& line, MeshRenderer * model, Mesh * mesh) {
	string faceString;
	int count = 0;
	
	vector<Vertex> prevVertices;

	while (line >> faceString) { // extract all vertex pointers from the line
		int slashIndex1 = faceString.find('/');
		int slashIndex2 = faceString.find('/', slashIndex1 + 1);
		size_t positionIndex = stoi(faceString.substr(0, slashIndex1)) - 1;
		size_t texIndex = stoi(faceString.substr(slashIndex1 + 1, slashIndex2)) - 1;
		size_t normalIndex = stoi(faceString.substr(slashIndex2 + 1, faceString.length())) - 1;
		if (count <= 2) { //triangle 1
			Vertex v = Vertex();
			v.Position = positions[positionIndex];
			v.Normal = normals[normalIndex];
			v.TexCoords = textureCoordinates[texIndex];
			model->AddVertex(v);
			mesh->AddIndex(vertexCount++);
			prevVertices.push_back(v);
		}
		else if (count >= 3) { //oh damn son we got a polygon
			Vertex v = Vertex();
			v.Position = positions[positionIndex];
			v.Normal = normals[normalIndex];
			v.TexCoords = textureCoordinates[texIndex];
			model->AddVertex(prevVertices[0]);
			mesh->AddIndex(vertexCount++);
			model->AddVertex(prevVertices[count-1]);
			mesh->AddIndex(vertexCount++);
			model->AddVertex(v);
			mesh->AddIndex(vertexCount++);
			prevVertices.push_back(v);
		}
		count++;
	}
}