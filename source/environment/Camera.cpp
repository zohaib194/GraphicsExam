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
	return glm::perspective(glm::radians(zoom), windowSize().x / windowSize().y, 0.1f, -10.0f);	
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

auto environment::Camera::getFollow() -> bool {
	return this->follow;
}

auto environment::Camera::update() -> void {

	glm::vec3 gliderPos = glider->getPos();
	glm::vec3 gliderDir = glider->getDirection();
	glm::vec3 oldPos = this->pos + glm::vec3(50.0f, 30.0f, 0.0f);

	if(follow){
		//this->pos = glm::vec3(50.0f, 30.0f, 0.0f);
		//glm::vec3 rotation =  glider->getRotationQuaternion() * this->pos;//glm::vec3(1.0f, 0.0f, 0.0f);
		//float offsetX = (float) (50.0f * sin(glm::radians(rotation.y)));
		//float offsetZ = (float) (50.0f * cos(glm::radians(rotation.y)));
		//this->pos.x = gliderPos.x - offsetX;
		//this->pos.z = gliderPos.z - offsetZ;
		//this->pos.y = gliderPos.y + 30.0f;

		//this->rotateBy(180 - glider.)
		//float angle = acos(dot(normalize(gliderPos - this->pos), normalize(glider->getDirection())));

		//this->pos.x = gliderPos.x - (float) (50.0f * sin(angle)); //glm::vec3(50.0f, 30.0f, 0.0f);
		//this->pos.y = gliderPos.y + 30.0f; //glm::vec3(50.0f, 30.0f, 0.0f);
		//this->pos.z = gliderPos.z - (float) (0.0f * cos(angle)); //glm::vec3(50.0f, 30.0f, 0.0f);


		float angle = acos(dot(normalize(gliderPos - this->pos), normalize(glider->getDirection())));

		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(), angle, normalize(glider->getDirection()));

		// Rotate camera's current position with rotation around horizontal rotation axis (0, 1, 0).
		this->target = (glm::vec3) (rotationMatrix * glm::vec4(this->target, 0));

		//this->target = glm::normalize(gliderPos - this->pos);
		//this->up = glider->getRotationQuaternion() * glm::vec3(0.0f, 1.0f, 0.0f);
		
		//this->translateBy(this->target);
	//	printf("%f, %f, %f\n", this->target.x, this->target.y, this->target.z);
	//	printf("%f, %f, %f\n", this->pos.x, this->pos.y, this->pos.z);
	//	printf("%f, %f, %f\n", gliderPos.x, gliderPos.y, gliderPos.z);
	//	printf("%f\n", sin(glm::radians(angle)));

		//this->pos = glm::vec3(50.0f, 30.0f, 0.0f);
		//this->pos =  glider->getRotationQuaternion() - this->pos;
		//this->pos = gliderPos - this->pos;

		//glm::vec3 cameraDirection = glm::normalize(this->pos - this->target);
		//this->target = glm::normalize(gliderPos - this->pos);
		//glm::vec3 cameraRight = glm::normalize(glm::cross(this->up, cameraDirection));
		//this->up = glm::cross(cameraDirection, cameraRight);//glider->getRotationQuaternion() * glm::vec3(0.0f, 1.0f, 0.0f);

	} else {
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		
	}

}

auto environment::Camera::setZoom(float zoom) -> void{
	if(this->zoom > 10.0f && this->zoom < 170.0) {
		this->zoom += zoom;
	} else if (this->zoom >= 10.0f && zoom == -1){
		this->zoom += zoom;
	} else if(this->zoom < 170.0 && zoom == 1){
		this->zoom += zoom;	
	}
}

auto environment::Camera::getTarget() -> glm::vec3 {
	return this->target;
}