#include "../environment/Camera.hpp"
#include "../game/Glider.hpp"
#include "../header/globalVar.hpp"
#include "../helpers/global_function.hpp"

extern game::Glider* glider;

environment::Camera::Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up) {
	this->pos = pos;
	this->target = target;
	this->up = up;
}

glm::vec2 environment::Camera::windowSize(){
	
	const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	return {videoMode->width * (relativeWindowSize.x / 100.0f),
		videoMode->height * (relativeWindowSize.y / 100.0f)};
}

void environment::Camera::setPos(glm::vec3 pos){
	this->pos = pos;
}

void environment::Camera::setDir(glm::vec3 target){
	this->target = target;
}

void environment::Camera::setUp(glm::vec3 up){
	this->up = up;
}

glm::vec3 environment::Camera::getPos(){
	return this->pos;
}

glm::vec3 environment::Camera::getDir(){
	return this->target;
}

glm::vec3 environment::Camera::getUp(){
	return this->up;
}

glm::mat4 environment::Camera::getViewMatrix(){
	return glm::lookAt(this->pos, this->pos + this->target, this->up);
}

glm::mat4 environment::Camera::getPerspectiveMatrix(){
	return glm::perspective(PI / 3.0f, windowSize().x / windowSize().y, 0.1f, -10.0f);	
}

void environment::Camera::rotateBy(float angleX, float angleY){
	// Get rotation matrix for "angle" amount, around horizontal rotation axis (0, 1, 0).
	glm::mat4 rotationHorMatrix = glm::rotate(glm::mat4(), angleX, horRotAxis);

	// Rotate camera's current position with rotation around horizontal rotation axis (0, 1, 0).
	this->target = (glm::vec3) (rotationHorMatrix * glm::vec4(this->target, 0));

	// Rotate vertical rotation axis with same rotation matrix to 
	// accomodate for horizontal rotation (around (0, 1, 0)). 
	this->vertRotAxis = (glm::vec3) (rotationHorMatrix * glm::vec4(vertRotAxis, 0));

	// Get rotation matrix for "angle" amount, around vertical rotation axis ("vertRotAxis").
	glm::mat4 rotationVertMatrix = glm::rotate(glm::mat4(), angleY, vertRotAxis);

	// Rotate camera's current position with rotation around vertical rotation axis ("vertRotAxis").
	this->target = (glm::vec3) (rotationVertMatrix * glm::vec4(this->target, 0));

	// Update cameras up with all rotations
	//this->up = (glm::vec3) ((rotationHorMatrix * rotationVertMatrix) * glm::vec4(this->up, 0)); 

	//TODO:
	//  - Add rotation on "z"-axis dependent on horizontal rotation.
	//  - Calculate cross("camera direction", "horizontal rotation axis") to get vertical z rotation axis
	//  - Use above caluclation to calc cross("horizontal rotation axis", "vertical z rotation axis") to get vertical x rotation axis.
	//  - Implement axis selection on which axis ot affect with mouse. Use dot product and most negative isn't affected.
}

void environment::Camera::translateBy(glm::vec3 translate){
	//glm::mat4 translationMatrix = glm::translate(glm::mat4(), translate);
	//this->pos = (glm::vec3) (translationMatrix * glm::vec4(pos, 0));
	this->pos += translate;
}

auto environment::Camera::followGlider(bool follow) -> void {
	this->follow = follow;
}

auto environment::Camera::update() -> void {
	glm::vec3 gliderDirection = glider->getDirection();
	glm::vec3 gliderPos = glider->getPos();
	
	if(follow){
		float angle = glider->getAngle();
		
		glm::vec3 diff = this->pos - gliderPos;
		
		this->model = glm::rotate(glm::mat4(), angle, gliderPos);//glm::rotate(this->model, glm::radians(angle), gliderDirection);
		this->pos = glm::vec3(gliderPos.x, gliderPos.y + 20.0f, gliderPos.z - 20.0f);// * 2.0f;
		this->model = glm::translate(glm::mat4(), this->pos);
		this->target = (glm::vec3) (model * glm::vec4(this->target, 0));
	}
}