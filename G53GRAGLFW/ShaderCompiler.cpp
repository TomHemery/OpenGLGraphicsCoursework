#include "ShaderCompiler.h"
#include "Shader.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Engine.h"

//Returns integer pointer to shader 
int ShaderCompiler::CompileShader(string filename, GLenum type) {
	//Get shader content
	string stdContent = FileToString(filename).c_str();
	//Get c string shader content
	const char * content = stdContent.c_str();

	//create a shader
	int shader = glCreateShader(type);
	//Compile the shader using GL
	glShaderSource(shader, 1, &content, NULL);
	glCompileShader(shader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		cerr << "ERROR, shader compilation failed\n" << infoLog << endl;
	}
	else {
		cout << "Successfully compiled shader with index: " << shader << endl;
	}
	return shader;
}

//creates a shader program, registers it with the engine and then returns it
Shader * ShaderCompiler::CreateProgram(string vertexShaderFilename, string fragmentShaderFilename) {
	int shaderProgramID = glCreateProgram();
	int vertexShader = CompileShader(vertexShaderFilename, GL_VERTEX_SHADER);
	int fragmentShader = CompileShader(fragmentShaderFilename, GL_FRAGMENT_SHADER);
	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);
	// check for linking errors
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
		cerr << "ERROR shader program linking failed\n" << infoLog << endl;
	}
	else {
		cout << "Successfully created shader program" << endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	Shader * newShader = new Shader(shaderProgramID);
	Engine::RegisterShader(newShader);
	return newShader;
}

//Takes a filename string an returns a string containing the full text of the file
string ShaderCompiler::FileToString(const string& filename) {
	ifstream in("../Shaders/" + filename);
	if (in) {
		std::stringstream buffer;
		buffer << in.rdbuf();
		return buffer.str();
	}
	else {
		cout << "Couldn't find shader: " << filename << endl;
		return "";
	}
}