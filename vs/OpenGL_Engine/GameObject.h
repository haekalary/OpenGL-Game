#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include "Shader.h"
#include "Transform.h"

class GameObject {
public:
	GameObject();
	~GameObject();
	Transform transform;
	void BuildShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	void BuildObject(GLfloat vertices[], GLuint verticesSize, GLuint indices[], GLuint indicesSize);
	void Render();
	Shader shader;
	GLuint GetObjectShaderID();
	GLuint GetVAO();
	GLuint GetVBO();
	GLuint GetEBO();
private:
	GLuint texture, VAO, VBO, EBO;
};

#endif