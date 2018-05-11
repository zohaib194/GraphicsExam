#pragma once

#include "../modeler/Shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>

// Boilder plate code needed to avoid circular inclusion with IComponent
namespace components
{
	class IComponent;
}

/**
 * @brief Container for content specific to chess game.
 */
namespace game
{
	/**
	 * @brief General Object with components.
	 */
	class HeightMap
	{
	public:
		
		/**
		 * @brief HeightMap constructor.
		 */
		HeightMap(char* path, int x, int z);

		/**
		 * @brief 
		 */
		~HeightMap();

		/**
		 * @brief 
		 * 
		 * @param component - component added to current obect.
		 */
		auto registerComponent(components::IComponent* component) -> bool;

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

	
		/**
		 * @brief Uses bezeir curve to interpolate between three control points. 
		 * 
		 * @param a - Control point is current location.
		 * @param b - Control point is middle of point a and b.
		 * @param c - Control point is destination location.
		 * @param dt - Delta time.
		 * @return Interpolated vector between 3 points.
		 */
		//auto jumpCurve(glm::vec3 a, glm::vec3 b, glm::vec3 c, float dt) -> glm::vec3;
			
		/**
		 * @brief Uses LERP to interpolate between two control points.
		 * 
		 * @param a - Control point is current location.
		 * @param b - Control point is destination location.
		 * @param dt - Delta time.
		 * @return Interpolated vector between 2 points.
		 */
		//auto lerp(glm::vec3 a, glm::vec3 b, float dt) -> glm::vec3;

		auto setPos(glm::vec3 newPos) -> void;

		auto loadMap(char* path) -> void;

		auto computeNormals() -> void;

		auto computeVertices() -> void;
		
		auto 
	private:

		std::vector<components::IComponent*> componentList;
		
		int width;				//!< x plane
		int length;				//!< z plane
		float **map;			//!< height values
		glm::vec3** normals;	//!< normals
		std::vector<int> vertices; 	//!< vertrices
		std::vector<int> indices; 	//!< vertrices
		glm::vec3 position;								//!< Origin of board.

		modeler::Shader* shaderProgram;					//!< Shaderprogram used by board for drawing.
	};
}