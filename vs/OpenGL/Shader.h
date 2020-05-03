#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader {
public:
	Shader();
	~Shader();
	void BuildShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	GLuint GetShaderID();
	void UseShader();
	void CheckShaderErrors(GLuint shader, string type);
private :
	GLuint shaderID;
};
#endif