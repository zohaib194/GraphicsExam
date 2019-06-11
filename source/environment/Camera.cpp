#include "../environment/Camera.hpp"
#include "../game/Glider.hpp"
#include "../header/globalVar.hpp"
#include "../helpers/global_function.hpp"

extern game::Glider* glider;

environment::Camera::Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up, float yaw, float pitch) {
	this->pos = pos;
	this->target = target;
	this->up = up;
	this->yaw = yaw;
	this->pitch = pitch;
	this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->movementSpeed = 2.5f;
	this->mouseSensitivity = 0.1f;
	updateCameraVectors();
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
	angleX *= mouseSensitivity;
	angleY *= mouseSensitivity;

	this->yaw += angleX;
	this->pitch += angleY;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (this->pitch > 89.0f) {
		this->pitch = 89.0f;
	}
	if (this->pitch < -89.0f){
		this->pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
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
		this->pos = gliderPos + glm::vec3(20.0f * cos(glm::radians(glider->getAngle() * -1)), 10.0f, 20.0f * sin(glm::radians(glider->getAngle() * -1)));
		this->target = glm::normalize(gliderPos - this->pos);
		this->up = glm::vec3(0, 1, 0);
		printf("%f\n", glider->getAngle());
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

auto environment::Camera::updateCameraVectors() -> void {
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	front.y = sin(glm::radians(this->pitch));
	front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->target = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	this->right = glm::normalize(glm::cross(this->target, this->worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	this->up = glm::normalize(glm::cross(this->right, this->target));
}