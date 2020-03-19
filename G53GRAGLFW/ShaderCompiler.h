#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Shader;

using namespace std;

//Compiles a shader or creates a full shader program
class ShaderCompiler
{
	static string FileToString(const string& filename);
public:
	//Returns a pointer to a shader as loaded on the GPU
	static int CompileShader(string filename, GLenum type);
	//Returns a shader program to be used in rendering
	static Shader * CreateProgram(string vertexShaderFilename, string fragmentShaderFilename);
};