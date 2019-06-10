#pragma once
#include "../modeler/Model.hpp"
#include "../modeler/struct.hpp"
#include "../modeler/Shader.hpp"
#include "libs/glm/glm/glm.hpp"
#include "libs/glm/glm/gtc/matrix_transform.hpp"
#include <string>
#include <vector>
#include "libs/glm/glm/gtx/quaternion.hpp"


/**
 * @brief Container for content specific to map game.
 */
namespace game {
	/**
	 * @brief General Object with components.
	 */
	class Glider : modeler::Model {
	public:
		
		/**
		 * @brief Glider constructor.
		 */
		Glider(char* path);

		/**
		 * @brief 
		 */
		~Glider();

		/**
		 * @brief updates state for next frame.
		 * 
		 * @param dt - Deltatime since last frame.
		 */
		auto update(float dt) -> void;

		/**
		 * @brief Draw the Glider.
		 */
		auto draw(float dt) -> void;

		auto setPos(glm::vec3 newPos) -> void;

		auto setOrientation(glm::vec3 direction, float angle) -> void;		

		auto addOnSpeed(float newSpeed) -> void;

		auto subFromSpeed(float speed) -> void;

		auto getSpeed() -> float;

		auto getPos() -> glm::vec3;

		auto getAngle() -> float;

		auto getDirection() -> glm::vec3;

		auto respawn(glm::vec3) -> void;

		auto resetToPrevPosition() -> void;

		auto getRotationQuaternion() -> glm::quat;
	private:

		glm::vec3 position;						

		glm::vec3 prevPosition;

		glm::mat4 model;
		
		glm::mat4 translation;
		glm::mat4 rotation;
		glm::mat4 scale = glm::mat4(1);
		glm::quat rotQuat;
	
		glm::vec3 direction;

		float speed = 1.0f;

		float angle = 0.0f;

		modeler::Shader* shaderProgram;					//!< Shaderprogram used by board for drawing.
	};
}