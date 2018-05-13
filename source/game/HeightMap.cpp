#include "HeightMap.hpp"
#include <SOIL/SOIL.h>
#include "../environment/Camera.hpp"
#include "../environment/LightSource.hpp"
#include "../modeler/ShaderManager.hpp"
//#include "../components/GraphicsComponent.hpp"

extern environment::Camera* camera;
extern modeler::ShaderManager* shaderManager;
extern environment::LightSource* lightSource;
float rotationTime = 0.0f;

game::HeightMap::HeightMap(char* path, float x, float z) : Model()
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	

	this->width = x;
	this->length = z;

	// Allocate memory for map height values.
	map = new float*[length];
	for (int i = 0; i < length; i++)
	{
		map[i] = new float[width];
	}


	loadMap(path);

	computeVertices();
	computeIndices();
	

	color = new glm::vec3[vertices.size()];

	//computeNormals();

	std::vector<modeler::TextureA> textures;
	
	this->meshes.push_back(modeler::Mesh(vertices, indices, textures));

	shaderProgram = shaderManager->getShader(std::vector<std::pair<GLenum, std::string>>{
		{GL_VERTEX_SHADER, "../shader/vertex.vert"},
		{GL_FRAGMENT_SHADER, "../shader/fragment.frag"},
	});
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
		{"lightColorID", "lightColor"},
		{"timeID", "time"}
	}));

	glUniform1f(uniforms["attenuationAID"], attenuation.x);
	glUniform1f(uniforms["attenuationBID"], attenuation.y);
	glUniform1f(uniforms["attenuationCID"], attenuation.z);
	glUniform1f(uniforms["ambientCoefficientID"], ambientCoefficient);
	glUniform1i(uniforms["specularExponentID"], specularExponent);
	glUniform3fv(uniforms["lightColorID"], 1, value_ptr(lightColor));
	glUniform3fv(uniforms["lightSourcePositionID"], 1, value_ptr(lightPosition));

/*
	for (int i = 0; i < vertices.size(); ++i)
	{
		printf("All heightvalue: %f\n", vertices[i].Position.y);
		if(highestPoint >= vertices[i].Position.y){
			highestPoint = vertices[i].Position.y;
			//printf("heightvalue: %f\n", vertices[i].Position.y);
		}
		if(vertices[i].Position.y < 15.0f) {
			
			color = glm::vec3(0.0f, 0.0f, 7.0f);
			//printf("Passed1\n");

		} else if(vertices[i].Position.y > 15.0f  && vertices[i].Position.y <= 20.0f) {
			
			color = glm::vec3(0.0f, 7.0f, 0.0f);
			//printf("Passed2\n");

		} else if(vertices[i].Position.y > 20.0f  && vertices[i].Position.y <= 25.0f){
			color = glm::vec3(0.4f, 0.5f, 0.0f);
			//printf("Passed3\n");

		} else {
			color = glm::vec3(1.0f, 1.0f, 1.0f);
		}

	}

*/
	glUniform1f(uniforms["timeID"], dt);
	glUniform3fv(uniforms["camPosID"], 1, value_ptr(camera->getPos()));												//glm::mat4 model = glm::rotate(glm::mat4(), time, glm::vec3(0, 1, 0));

	glUniformMatrix4fv(uniforms["viewID"], 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(uniforms["projectionID"], 1, GL_FALSE, glm::value_ptr(projection));

	glm::mat4 modelm;
	rotationTime += dt;
	modelm = glm::translate(modelm, this->position); // Translate it down so it's at the center of the scene.
	//printf("%f, %f, %f\n",position.x, position.y, position.z );
	//modelm = glm::scale(modelm, glm::vec3(0.002f, 0.002f, 0.002f));	
	glUniformMatrix4fv(uniforms["modelID"], 1, GL_FALSE, glm::value_ptr(modelm));
	
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(view*modelm)));

	glUniformMatrix3fv(uniforms["normalMatrixID"], 1, GL_FALSE, glm::value_ptr(normalMatrix));

/*	
	if (this->componentList.at(0))
		this->componentList.at(0)->draw(*shaderProgram);
*/
	
	this->Draw(*shaderProgram);

	shaderProgram->unbind();
}

auto game::HeightMap::setPos(glm::vec3 newPos) -> void {
	this->position = newPos;
}

auto game::HeightMap::loadMap(char* path) -> void{
	unsigned int color;
	int w, h;
	unsigned char* image = SOIL_load_image(path, &w, &h, 0, SOIL_LOAD_L);

	this->size = glm::vec3(w / this->width, (this->width / 2.0f) / 255.0f, h / this->length);

	printf("Size: %f\n", size.y);
	for (int y = 0; y < this->length; y++)
	{
		for (int x = 0; x < this->width; x++)
		{
			color = image[(y * w + x)];

			float height = size.y * color;

			map[y][x] = height;

		}
	}
}

auto game::HeightMap::computeNormals() -> void {
	glm::vec3 normal;
	for (int i = 0; i < indices.size(); i += 2)
	{	
		normal.x = (vertices[i].Position.y * vertices[i+1].Position.z) - (vertices[i].Position.z * vertices[i+1].Position.y);
		normal.y = (vertices[i].Position.z * vertices[i+1].Position.x) - (vertices[i].Position.x * vertices[i+1].Position.z);
		normal.z = (vertices[i].Position.x * vertices[i+1].Position.y) - (vertices[i].Position.y * vertices[i+1].Position.x);
		
		vertices[i].Normal = normal;
		vertices[i+1].Normal = normal;
	}
}

auto game::HeightMap::computeVertices() -> void {
	modeler::Vertex vertex;
	
	for (int z = 0; z < this->length; ++z)
	{
		for (int x = 0; x < this->width; x++)
		{

			vertex.Position = glm::vec3(x * size.x, map[z][x], z * size.z);
			vertex.Normal = glm::vec3(0.0f, 1.0f, 0.0f);
			vertices.push_back(vertex);

		}
	}
}

auto game::HeightMap::computeIndices() -> void {

	for (int i = 0; i < this->length - 1; ++i)
	{
		for (int j = 0; j < this->width - 1; ++j)
		{
			indices.push_back(j + (this->width * i));
			indices.push_back((j + 1) + (this->width * i));
			indices.push_back(j + (this->width * (i + 1)));
	
			indices.push_back(j + (width * (i + 1)));
			indices.push_back((j + 1) + (this->width * i));
			indices.push_back((j + 1) + (this->width * (i + 1)));
		}
	}

	for (int i = 0; i < indices.size() /10000; ++i)
	{
		//printf("%d\t", indices[i]);
	}
}

auto game::HeightMap::getWidthHeight() -> std::pair<float, float>{
	return std::pair<float, float>(this->width, this->length);
}

/*
auto game::HeightMap::computeColors(){
	for (int i = 0; i < vertices.size(); ++i)
	{
		if(vertices[i].Position.y < 15.0f) {
			if(vertices[i].Position.y > 10.0f){

			}
			//printf("Passed1\n");

		} else {
			color = glm::vec3(0.0f, 0.0f, 7.0f);
		}



		if(vertices[i].Position.y > 15.0f  && vertices[i].Position.y <= 20.0f) {
			
			color = glm::vec3(0.0f, 7.0f, 0.0f);
			//printf("Passed2\n");

		} else if(vertices[i].Position.y > 20.0f  && vertices[i].Position.y <= 25.0f){
			color = glm::vec3(0.4f, 0.5f, 0.0f);
			//printf("Passed3\n");

		} else {
			color = glm::vec3(1.0f, 1.0f, 1.0f);
		}
		glUniform3fv(uniforms["colorID"], 1, value_ptr(this->color));

	}
}


auto game::HeightMap::lerp(glm::vec3 a, glm::vec3 b, float dt) -> glm::vec3 {
	glm::vec3 point;

	point.x = a.x * (1 - dt) + b.x * dt;
	point.y = a.y * (1 - dt) + b.y * dt;
	point.z = a.z * (1 - dt) + b.z * dt;

	return point;
}
*/