#include "Transform.h";

Transform::Transform() {

}

Transform::~Transform() {

}

void Transform::Translate(glm::vec3 direction) {
	position += direction;
}

void Transform::Rotate(glm::vec3 direction, float angle) {
	rotationDirectionTemp = direction;
	angleTemp += angle;
}

void Transform::Scale(glm::vec3 scale) {
	this->scale = scale;
}

void Transform::SetOrigin(glm::vec3 origin) {
	this->origin = origin;
}

void Transform::SetPosition(glm::vec3 newPosition) {
	position = newPosition;
}

void Transform::Execute(Shader shader) {
	shader.UseShader();

	model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(angleTemp), rotationDirectionTemp);
	model = glm::scale(model, scale);
	model = glm::translate(model, origin);

	glUniformMatrix4fv(glGetUniformLocation(shader.GetShaderID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
}