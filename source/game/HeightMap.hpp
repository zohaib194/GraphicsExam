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
	class HeightMap : modeler::Model {
	public:
		
		/**
		 * @brief HeightMap constructor.
		 */
		HeightMap(char* path, float x, float z);

		/**
		 * @brief 
		 */
		~HeightMap();

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

		auto getWidthHeight() -> std::pair<float, float>;

		auto loadMap(char* path) -> void;

		auto computeNormals() -> void;

		auto computeVertices() -> void;
		
		auto computeIndices() -> void;

		auto setContour(bool displayContour) -> void;

		auto getContour() -> float;

		auto setDay(int day) -> void;

		auto setSeason(int season) -> void;

		auto getSeason() -> int;

		auto setSeasonMode(int mode) -> void;

		auto getSeasonMode() -> int;

		auto pauseSeasons(bool pause) -> void;
		
		auto isPause() -> bool;
	private:

		//std::vector<components::IComponent*> componentList;
		glm::vec3 size;			//!< size of the terrain.
		int width;				//!< x plane
		int length;				//!< z plane
		float **map;			//!< height values

		glm::vec3** normals;	//!< normals
		std::vector<modeler::Vertex> vertices; 	//!< vertrices
		std::vector<unsigned int> indices; 	//!< vertrices
		glm::vec3 position;								//!< Origin of board.
		
		glm::vec3* color;
		bool contour = false;

		int day;
		int season;
		int seasonMode = 0;
		bool pause = false;

		modeler::Shader* shaderProgram;					//!< Shaderprogram used by board for drawing.
	};
}