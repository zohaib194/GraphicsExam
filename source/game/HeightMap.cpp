#include "HeightMap.hpp"
#include <SOIL/SOIL.h>
#include "../environment/Camera.hpp"
#include "../environment/LightSource.hpp"
#include "../modeler/ShaderManager.hpp"
#include "../components/GraphicsComponent.hpp"

extern environment::Camera* camera;
extern modeler::ShaderManager* shaderManager;
extern environment::LightSource* lightSource;
float rotationTime = 0.0f;

game::HeightMap::HeightMap(char* path, int x, int z)
{
	loadMap(path);
	shaderProgram = shaderManager->getShader(std::vector<std::pair<GLenum, std::string>>{
		{GL_VERTEX_SHADER, "../shader/vertex.vert"},
		{GL_FRAGMENT_SHADER, "../shader/fragment.frag"},
	});
}

auto game::HeightMap::registerComponent(components::IComponent* component) -> bool
{
	// If this is a valid component
	if (component)
	{
		// Add parent / initialize with current obect as parent
		component->init(this);
		// Add it to current objects component list
		this->componentList.push_back(component);
	}

	// Tell whether it was added or not
	return (component);
}

auto game::HeightMap::update(float dt) -> void
{
	
}

auto game::HeightMap::draw(float dt) -> void
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
		{"lightColorID", "lightColor"}
	}));

	glUniform1f(uniforms["attenuationAID"], attenuation.x);
	glUniform1f(uniforms["attenuationBID"], attenuation.y);
	glUniform1f(uniforms["attenuationCID"], attenuation.z);
	glUniform1f(uniforms["ambientCoefficientID"], ambientCoefficient);
	glUniform1i(uniforms["specularExponentID"], specularExponent);
	glUniform3fv(uniforms["lightColorID"], 1, value_ptr(lightColor));
	glUniform3fv(uniforms["lightSourcePositionID"], 1, value_ptr(lightPosition));

	glUniform3fv(uniforms["camPosID"], 1, value_ptr(camera->getPos()));												//glm::mat4 model = glm::rotate(glm::mat4(), time, glm::vec3(0, 1, 0));

	glUniformMatrix4fv(uniforms["viewID"], 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(uniforms["projectionID"], 1, GL_FALSE, glm::value_ptr(projection));

	glm::mat4 modelm;
	rotationTime += dt;
	//modelm = glm::translate(modelm, this->position); // Translate it down so it's at the center of the scene.
	//printf("%f, %f, %f\n",position.x, position.y, position.z );
	modelm = glm::scale(modelm, glm::vec3(1.1f, 1.1f, 1.1f));	
	modelm = glm::rotate(modelm, rotationTime, glm::vec3(1.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniforms["modelID"], 1, GL_FALSE, glm::value_ptr(modelm));
	
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(view*modelm)));

	glUniformMatrix3fv(uniforms["normalMatrixID"], 1, GL_FALSE, glm::value_ptr(normalMatrix));
/*	
	if (this->componentList.at(0))
		this->componentList.at(0)->draw(*shaderProgram);
*/

	Mesh mesh = Mesh()
	shaderProgram->unbind();
}

auto game::HeightMap::setPos(glm::vec3 newPos) -> void {
	this->position = newPos;
}

auto game::HeightMap::loadMap(char* path) -> void{
	unsigned int color;
	int w, h;
	unsigned char* image = SOIL_load_image(path, &w, &h, 0, SOIL_LOAD_L);

	this->width = w;
	this->length = h;
	// Allocate memory for map height values.
	map = new float*[length];
	for (int i = 0; i < length; i++)
	{
		map[i] = new float[width];
	}

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			color = image[(y*w+x)];

			float height = (this->width/4) * (color / 225.0f) * 0.5;

			map[y][x] = height;

		}
	}

}

auto game::HeightMap::computeNormals() -> void {

}

auto game::HeightMap::computeVertices() -> void {
	for (int z = 0; z < this->length; ++z)
	{
		for (int x = 0; x < this->width; x++)
		{
			vertices.push_back(x);
			vertices.push_back(map[z][x]);
			vertices.push_back(z);
		}
	}
}

