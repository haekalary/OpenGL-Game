#include "GameObject.h"

GameObject::GameObject() {
	
}

GameObject::~GameObject() {

}

void GameObject::BuildShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath) {
	shader.BuildShader(vertexPath, fragmentPath, geometryPath);
}

void GameObject::BuildObject(GLfloat vertices[], GLuint verticesSize , GLuint indices[], GLuint indicesSize) {

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}

void GameObject::Render() {
	shader.UseShader();
}

GLuint GameObject::GetObjectShaderID() {
	return shader.GetShaderID();
}

GLuint GameObject::GetVAO() {
	return VAO;
}

GLuint GameObject::GetVBO() {
	return VBO;
}

GLuint GameObject::GetEBO() {
	return EBO;
}