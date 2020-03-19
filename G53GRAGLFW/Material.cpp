#include "Material.h"
#include "Texture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Engine.h"
#include "Shader.h"

Material::Material(const string& _name): 
	name(_name)
{
}

Material::~Material()
{

}

void Material::Use() {
	//set everything up in the shader, and also bind the textures 
	glBindTexture(GL_TEXTURE_2D, 0);
	if (diffuseMap != nullptr) {
		glActiveTexture(GL_TEXTURE0);
		diffuseMap->Use();
	}
	if (specularMap != nullptr) {
		glActiveTexture(GL_TEXTURE1);
		specularMap->Use();
	}
	Engine::GetDefaultShaderProgram()->Use();
	Engine::GetDefaultShaderProgram()->SetFloat("material.shininess", shininess);
}