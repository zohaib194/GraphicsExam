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

		auto setPos(glm::vec3 newPos ) -> void;

	private:

		//std::vector<components::IComponent*> componentList;
		glm::vec3 size;
		int width;				//!< x plane
		int length;				//!< z plane
		float **map;			//!< height values

		glm::vec3** normals;	//!< normals
		std::vector<modeler::Vertex> vertices; 	//!< vertrices
		std::vector<unsigned int> indices; 	//!< vertrices
		glm::vec3 position;								//!< Origin of board.
		
		glm::vec3* color;
		
		modeler::Shader* shaderProgram;					//!< Shaderprogram used by board for drawing.
	};
}