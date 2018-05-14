#include "LightSource.hpp"

#include <GLFW/glfw3.h>

environment::LightSource::LightSource(){
	this->position = {250.0f, 50.0f, 600.0f};
	this->lightColor = {1.0f, 1.0f, 1.0f};
	this->attenuation = {1.0f, 1.0f, 1.0f};
	this->ambientCoefficient = 0.2f;
	this->specualarExponent = 32.0f;
	this->rotationPoint = this->position;
}

environment::LightSource::LightSource(glm::vec3 position, glm::vec3 lightColor, glm::vec3 attenuation, float ambientCoefficient, int specualarExponent){
	this->position = position;
	this->lightColor = lightColor;
	this->attenuation = attenuation;
	this->ambientCoefficient = ambientCoefficient;
	this->specualarExponent = specualarExponent;
	this->rotationPoint = this->position;
}

environment::LightSource::~LightSource(){

}

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


auto environment::LightSource::update(float dt) -> void {
	this->lightColor = glm::vec3(0.0f, 0.0f, 0.7f) * float(cos(dt * (2 * 3.14f)) * 600.0f + rotationPoint.x);
	this->position = glm::vec3(cos(dt * (2 * 3.14f)) * 600.0f + rotationPoint.x, sin(dt * (2 * 3.14f)) * 400.0f + rotationPoint.y, rotationPoint.z);
}

auto environment::LightSource::setUpdate(bool update) -> void{
	this->shouldUpdate = update;
}

auto environment::LightSource::getUpdate() -> bool{
	return this->shouldUpdate;
}