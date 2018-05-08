#include "LightSource.hpp"

#include <GLFW/glfw3.h>

environment::LightSource::LightSource(){
	this->position = {0.0f, 0.0f, 5.0f};
	this->lightColor = {1.0f, 1.0f, 1.0f};
	this->attenuation = {1.0f, 1.0f, 1.0f};
	this->ambientCoefficient = 0.1f;
	this->specualarExponent = 32.0f;
}

environment::LightSource::LightSource(glm::vec3 position, glm::vec3 lightColor, glm::vec3 attenuation, float ambientCoefficient, int specualarExponent){
	this->position = position;
	this->lightColor = lightColor;
	this->attenuation = attenuation;
	this->ambientCoefficient = ambientCoefficient;
	this->specualarExponent = specualarExponent;
}

environment::LightSource::~LightSource(){

}
/*
void environment::LightSource::update(float dt){
	// Rotate light for effect
	this->position = this->position * (glm::mat3)glm::rotate(glm::mat4(), dt, glm::vec3(0.0f, 1.0f, 0.0f));
}
*/
auto environment::LightSource::getAttenuation() -> glm::vec3{
	return this->attenuation;
}

auto environment::LightSource::getColor() -> glm::vec3{
	return this->lightColor;
}

auto environment::LightSource::getPosition() -> glm::vec3{
	return this->position;
}

auto environment::LightSource::getAmbientCoefficient() -> float{
	return this->ambientCoefficient;
}

auto environment::LightSource::getSpecularExponent() -> int{
	return this->specualarExponent;
}

void environment::LightSource::setPosition(glm::vec3 position){
	this->position = position;
}