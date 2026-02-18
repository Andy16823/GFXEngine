#include "Transform.h"

GFXEngine::Math::Transform::Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scl)
{
	position = pos;
	this->setRotationFromEuler(rot);
	scale = scl;
}

glm::mat4 GFXEngine::Math::Transform::getModelMatrix() const
{
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotationMat = glm::toMat4(rotation);
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);
	return translation * rotationMat * scaleMat;
}

void GFXEngine::Math::Transform::setRotationFromEuler(const glm::vec3& rot)
{
	glm::quat qPitch = glm::angleAxis(glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::quat qYaw = glm::angleAxis(glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat qRoll = glm::angleAxis(glm::radians(rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
	rotation = qYaw * qPitch * qRoll;
}

glm::vec3 GFXEngine::Math::Transform::getEulerRotation() const
{
	glm::vec3 euler = glm::eulerAngles(rotation);
	return glm::degrees(euler);
}

glm::vec3 GFXEngine::Math::Transform::getForward() const
{
	return rotation * glm::vec3(0.0f, 0.0f, -1.0f);
}

glm::vec3 GFXEngine::Math::Transform::getRight() const
{
	return rotation * glm::vec3(1.0f, 0.0f, 0.0f);
}

glm::vec3 GFXEngine::Math::Transform::getUp()
{
	return rotation * glm::vec3(0.0f, 1.0f, 0.0f);
}
