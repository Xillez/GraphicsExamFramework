#include "../header/camera.hpp"
#include "../header/globalVar.hpp"
#include "../header/global_function.hpp"


Camera::Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up) {
	this->pos = pos;
	this->target = target;
	this->up = up;
}

void Camera::setPos(glm::vec3 pos){
	this->pos = pos;
}

void Camera::setDir(glm::vec3 target){
	this->target = target;
}

void Camera::setUp(glm::vec3 up){
	this->up = up;
}

glm::vec3 Camera::getPos(){
	return this->pos;
}

glm::vec3 Camera::getDir(){
	return this->target;
}

glm::vec3 Camera::getUp(){
	return this->up;
}

glm::mat4 Camera::getViewMatrix(){
	return glm::lookAt(this->pos, this->target, this->up);
}

glm::mat4 Camera::getPerspectiveMatrix(){
	return glm::perspective(PI / 3.0f, windowSize().x / windowSize().y, 0.1f, -10.0f);	
}

void Camera::rotateBy(float angleX, float angleY){
	// Get rotation matrix for "angle" amount, around horizontal rotation axis (0, 1, 0).
	glm::mat4 rotationHorMatrix = glm::rotate(glm::mat4(), angleX, horRotAxis);

	// Rotate camera's current position with rotation around horizontal rotation axis (0, 1, 0).
	this->pos = (glm::vec3) (rotationHorMatrix * glm::vec4(pos, 0));

	// Rotate vertical rotation axis with same rotation matrix to 
	// accomodate for horizontal rotation (around (0, 1, 0)). 
	this->vertRotAxis = (glm::vec3) (rotationHorMatrix * glm::vec4(vertRotAxis, 0));

	// Get rotation matrix for "angle" amount, around vertical rotation axis ("vertRotAxis").
	glm::mat4 rotationVertMatrix = glm::rotate(glm::mat4(), angleY, vertRotAxis);

	// Rotate camera's current position with rotation around vertical rotation axis ("vertRotAxis").
	this->pos = (glm::vec3) (rotationVertMatrix * glm::vec4(pos, 0));

	// Update cameras up with all rotations
	this->up = (glm::vec3) ((rotationHorMatrix * rotationVertMatrix) * glm::vec4(this->up, 0));

	//TODO:
	//  - Add rotation on "z"-axis dependent on horizontal rotation.
	//  - Calculate cross("camera direction", "horizontal rotation axis") to get vertical z rotation axis
	//  - Use above caluclation to calc cross("horizontal rotation axis", "vertical z rotation axis") to get vertical x rotation axis.
	//  - Implement axis selection on which axis ot affect with mouse. Use dot product and most negative isn't affected.
}