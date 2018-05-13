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
	glm::mat4 gliderModel = glider->getModel();
	glm::vec3 gliderDirection = glider->getDirection();
	glm::vec3 gliderPos = glm::vec3(gliderModel * glm::vec4(glider->getPos(), 1.0f));
	printf("%s GliderPos: %f, %f, %f\n",  TAG_DEBUG.c_str() ,gliderPos.x, gliderPos.y, gliderPos.z);
	printf("%s gliderDirection: %f, %f, %f\n",  TAG_DEBUG.c_str() ,gliderDirection.x, gliderDirection.y, gliderDirection.z);
	printf("%s CameraPos: %f, %f, %f\n",  TAG_DEBUG.c_str(), pos.x, pos.y, pos.z);
	printf("%s CameraTarget: %f, %f, %f\n",  TAG_DEBUG.c_str(), target.x, target.y, target.z);
	if(follow){
		float angle = glider->getAngle();
		
		glm::vec3 diff = this->pos - gliderPos;
		
		//this->pos = glm::vec3(diff.x + 25.0f, diff.y + 10.0f, diff.z);// * 2.0f;
		//this->pos = glm::vec3(gliderPos.x + 25.0f, gliderPos.y + 10.0f, gliderPos.z);// * 2.0f;
		
		this->model = glm::rotate(glm::mat4(), angle, gliderDirection);//glm::rotate(this->model, glm::radians(angle), gliderDirection);
		this->pos = (glm::vec3)(model * (glm::vec4(gliderPos.x, gliderPos.y, gliderPos.z - 20.0f, 0) + 20.0f));// * 2.0f;
		this->model = glm::translate(glm::mat4(), this->pos);
		this->target = gliderPos;//(glm::vec3) (model * glm::vec4(this->target, 0));
		

		//this->target = glider->getPos();
//		glm::mat4 rotationHorMatrix = glm::rotate(glm::mat4(), angle, glm::vec3(1.0f, 0.0f, 0.0f));
//
//		this->pos = (glm::vec3) (rotationHorMatrix * glm::vec4(this->pos, 0));
		//this->up = glm::vec3(0.0f, 0.0f, 1.0f);
		

		//float angle = acos(glm::dot(this-pos, diff));


	}
}