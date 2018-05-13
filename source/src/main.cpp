#include "../helpers/glfw_setup.hpp"
#include "../helpers/global_function.hpp"
#include "../components/GraphicsComponent.hpp"
#include "../game/HeightMap.hpp"
#include "../game/Glider.hpp"
#include "../environment/Camera.hpp"
#include "../environment/LightSource.hpp"
#include "../header/globalVar.hpp"
#include "../modeler/ShaderManager.hpp"

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>

environment::Camera* camera;
environment::LightSource* lightSource;
GLFWwindow* window;
game::HeightMap* hm;
game::Glider* glider;
modeler::ShaderManager* shaderManager;

int main(int argc, char const *argv[])
{	
	// Create camera
	printf("%s Setting up camera\n",TAG_INFO.c_str());
	camera = new environment::Camera(glm::vec3(0, 100, 50), glm::vec3(2, -1, 2), glm::vec3(0, 1, 0));

	// Setting up light
	printf("%s Setting up LightSource\n",TAG_INFO.c_str());
	lightSource = new environment::LightSource();

	// Create common interface for shaders
	printf("%s Creating shadermanager\n", TAG_INFO.c_str());
	shaderManager = new modeler::ShaderManager();

	// OpenGL setup
	printf("%s Creating window\n", TAG_INFO.c_str());
	window = helpers::glfw_setup();
	
	// Make graphics component for "cube
	//components::GraphicsComponent* component = new components::GraphicsComponent("../asset/basic_sphere.obj");

	// Make cube
	printf("%s Creating board\n", TAG_INFO.c_str());
	hm = new game::HeightMap("../asset/heightmap/height100.png", 500.0f, 500.0f);
	glider = new game::Glider("../asset/model/glider.obj");
	glider->setPos(glm::vec3(0.0f, 80.0f, 0.0f));
	//hm->registerComponent(component);
	//component = nullptr;

	// setup event handler
	printf("%s Setting up event handler\n", TAG_INFO.c_str());
	helpers::setup_EventHandling();

	// Setting up time info for calculating deltatime (dt)
	float currentTime = 0.0f, lastTime = 0.0f, dt = 0.0f;
	lastTime = glfwGetTime();
	
	// Run until close event is given to the window
	printf("%s Starting gameloop\n", TAG_INFO.c_str());
	
    	//camera->followGlider(true);
	
	while(!glfwWindowShouldClose(window))
	{
		// Clearing screen for next draw
		glClearColor(0.4, 0.8, 0.8, 1);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Calculating delta time
		currentTime = glfwGetTime();
		dt = currentTime - lastTime;
		lastTime = currentTime;

		hm->draw(dt);
		glider->update(dt);
		camera->update();
		//camera->rotateBy(1.0f * dt, 0.0f * dt);
		//chessBoard->update(dt);
		glfwSwapBuffers(window);    // SWAP BUFFERS
        glfwPollEvents();           // LISTEN FOR WINDOW EVENTS

	}

	printf("%s Closing application\n", TAG_INFO.c_str());
	glfwDestroyWindow(window);

	return 0;
}