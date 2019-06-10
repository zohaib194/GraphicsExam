#include "Glider.hpp"
#include "libs/SOIL/src/SOIL.h"
#include "../environment/Camera.hpp"
#include "../environment/LightSource.hpp"
#include "../modeler/ShaderManager.hpp"
//#include "../components/GraphicsComponent.hpp"

extern environment::Camera* camera;
extern modeler::ShaderManager* shaderManager;
extern environment::LightSource* lightSource;

game::Glider::Glider(char* path) : Model(path)
{
	this->position = glm::vec3(50.0f, 100.0f, 600.0f);
	this->direction = glm::vec3(-1.0f, 0.0f, 0.0f);

	shaderProgram = shaderManager->getShader(std::vector<std::pair<GLenum, std::string>>{
		{GL_VERTEX_SHADER, "../shader/vertexGlider.vert"},
		{GL_FRAGMENT_SHADER, "../shader/fragmentGlider.frag"},
	});
}

auto game::Glider::update(float dt) -> void
{	
	this->position += (glm::normalize(this->direction) * -speed * dt);
	if(speed >= -1.0f){
		speed = -1.0f;
	}
	draw(dt);
}

auto game::Glider::draw(float dt) -> void
{
	this->shaderProgram->bind();

	glm::mat4 view = camera->getViewMatrix(); 
	
	glm::mat4 projection = camera->getPerspectiveMatrix();

	glm::vec3 lightPosition = lightSource->getPosition();
	glm::vec3 attenuation = lightSource->getAttenuation(); 
	glm::vec3 lightColor = lightSource->getColor();
	float ambientCoefficient = lightSource->getAmbientCoefficient();
	int specularExponent = lightSource->getSpecularExponent();

	std::map<std::string, GLuint> uniforms = shaderProgram->getUniform(	std::map<std::string, std::string>({
		{"viewID", "view"},
		{"projectionID", "projection"},
		{"modelID", "model"},
		{"normalMatrixID", "normalMatrix"},
		{"lightSourcePositionID","lightSourcePosition"},
		{"camPosID", "CamPos"},
		{"attenuationAID", "attenuationA"},
		{"attenuationBID", "attenuationB"},
		{"attenuationCID", "attenuationC"},
		{"ambientCoefficientID", "ambientCoefficient"},
		{"specularExponentID", "specularExponent"},
		{"lightColorID", "lightColor"},
	}));

	glUniform1f(uniforms["attenuationAID"], attenuation.x);
	glUniform1f(uniforms["attenuationBID"], attenuation.y);
	glUniform1f(uniforms["attenuationCID"], attenuation.z);
	glUniform1f(uniforms["ambientCoefficientID"], ambientCoefficient);
	glUniform1i(uniforms["specularExponentID"], specularExponent);
	glUniform3fv(uniforms["lightColorID"], 1, value_ptr(lightColor));
	glUniform3fv(uniforms["lightSourcePositionID"], 1, value_ptr(lightPosition));
	glUniform3fv(uniforms["camPosID"], 1, value_ptr(camera->getPos()));												
	glUniformMatrix4fv(uniforms["viewID"], 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(uniforms["projectionID"], 1, GL_FALSE, glm::value_ptr(projection));
	
	//modelm = glm::scale(modelm, glm::vec3(0.002f, 0.002f, 0.002f));	
	//model = glm::rotate(model, dt, glm::vec3(0, 1, 0));
	translation = glm::translate(glm::mat4(1), this->position); // Translate it down so it's at the center of the scene.
	//printf("%f, %f, %f\n",position.x, position.y, position.z );
	glm::mat4 model = translation * rotation * scale;
	glUniformMatrix4fv(uniforms["modelID"], 1, GL_FALSE, glm::value_ptr(model));
	
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(view*model)));

	glUniformMatrix3fv(uniforms["normalMatrixID"], 1, GL_FALSE, glm::value_ptr(normalMatrix));
	//model = glm::mat4();
/*	
	if (this->componentList.at(0))
		this->componentList.at(0)->draw(*shaderProgram);
*/
	
	this->Draw(*shaderProgram);

	shaderProgram->unbind();
}

auto game::Glider::setPos(glm::vec3 newPos) -> void {
	this->position = newPos;
}

auto game::Glider::setOrientation(glm::vec3 direction, float angle) -> void {	
	this->angle = glm::radians(angle);

	direction = glm::vec3(glm::radians(direction.x), glm::radians(direction.y), glm::radians(direction.z));

	rotQuat = glm::quat(direction);
	this->rotation *= glm::toMat4(rotQuat);
	//this->rotation = glm::quaternion(this->rotation, angle, direction);
	this->direction = glm::vec3(rotQuat * glm::vec4(this->direction, 0.0f));
}

auto game::Glider::addOnSpeed(float newSpeed) -> void {
	this->speed += newSpeed;
}

auto game::Glider::subFromSpeed(float speed) -> void {
	this->speed -= speed;	
}

auto game::Glider::getSpeed() -> float{
	return this->speed;
}

auto game::Glider::getPos() -> glm::vec3 {
	return this->position;
}

auto game::Glider::getAngle() -> float {
	return this->angle;
}

auto game::Glider::getDirection() -> glm::vec3 {
	return this->direction;
}

auto game::Glider::respawn(glm::vec3 newPosition) -> void {
	this->prevPosition = this->position;
	this->position = newPosition;
}

auto game::Glider::resetToPrevPosition() -> void {
	this->position = prevPosition;
}

auto game::Glider::getRotationQuaternion() -> glm::quat {
	return this->rotQuat;
}