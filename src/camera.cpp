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

void Camera::rotateBy(float angle, glm::vec3 axis){
	glm::mat4 rotatationMatrix = glm::rotate(glm::mat4(), angle, axis);
	
	this->pos = (glm::vec3) (rotatationMatrix * glm::vec4(pos, 0));
}