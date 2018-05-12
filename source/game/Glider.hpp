#pragma once
#include "../modeler/Model.hpp"
#include "../modeler/struct.hpp"
#include "../modeler/Shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>


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
		 * @brief HeightMap constructor.
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
		 * @brief Draw the board and every piece found.
		 */

		auto draw(float dt) -> void;

		auto setPos(glm::vec3 newPos) -> void;

		auto setOrientation(glm::vec3 direction) -> void;		

		auto addOnSpeed(float newSpeed) -> void;

		auto subFromSpeed(float speed) -> void;

		auto getSpeed() -> float;
	private:

		glm::vec3 position;								//!< Origin of board.
		
		glm::mat4 model;

		float speed = -0.1f;

		modeler::Shader* shaderProgram;					//!< Shaderprogram used by board for drawing.
	};
}