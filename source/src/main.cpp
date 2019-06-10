#include "../helpers/glfw_setup.hpp"
#include "../helpers/global_function.hpp"
#include "../game/HeightMap.hpp"
#include "../game/Glider.hpp"
#include "../environment/Camera.hpp"
#include "../environment/LightSource.hpp"
#include "../header/globalVar.hpp"
#include "../modeler/ShaderManager.hpp"

#include "GLFW/glfw3.h"
#include <stdio.h>
#include <iostream>

environment::Camera* camera;
environment::LightSource* lightSource;
GLFWwindow* window;
game::HeightMap* hm;
game::Glider* glider;
modeler::ShaderManager* shaderManager;

float hours = 0.0f;
int days = 0;
int season = 0;
float night = 0.0f;
float dayTime = 0.0f;

int main(int argc, char const *argv[])
{	
	// Create camera
	printf("%s Setting up camera\n",TAG_INFO.c_str());
	camera = new environment::Camera(glm::vec3(0, 400, 900), glm::vec3(1, -1, -2), glm::vec3(0, 1, 0));

	// Setting up light
	printf("%s Setting up LightSource\n",TAG_INFO.c_str());
	lightSource = new environment::LightSource();

	// Create common interface for shaders
	printf("%s Creating shadermanager\n", TAG_INFO.c_str());
	shaderManager = new modeler::ShaderManager();

	// OpenGL setup
	printf("%s Creating window\n", TAG_INFO.c_str());
	window = helpers::glfw_setup();
	
	// Imgui setup
//	printf("%s Setup ImGUI\n", TAG_INFO.c_str());
//    ImGui::CreateContext();
//    ImGuiIO& io = ImGui::GetIO(); (void)io;
//    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
//    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
//    ImGui_ImplGlfwGL3_Init(window, true);
//    ImGui::StyleColorsDark();

	printf("%s Creating board\n", TAG_INFO.c_str());
	hm = new game::HeightMap("../asset/heightmap/height100.png", 504.0f, 1004.0f);
	glider = new game::Glider("../asset/model/glider.obj");
	glider->setPos(glm::vec3(0.0f, 80.0f, 0.0f));

	// setup event handler
	printf("%s Setting up event handler\n", TAG_INFO.c_str());
	helpers::setup_EventHandling();

	// Setting up time info for calculating deltatime (dt)
	float currentTime = 0.0f, lastTime = 0.0f, dt = 0.0f;
	lastTime = glfwGetTime();
	
	// Run until close event is given to the window
	printf("%s Starting gameloop\n", TAG_INFO.c_str());
	
    	
	
	while(!glfwWindowShouldClose(window))
	{
		// Clearing screen for next draw
		glClearColor(0.4, 0.8, 0.8, 1);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Calculating delta time
		currentTime = glfwGetTime();
		dt = currentTime - lastTime;
		lastTime = currentTime;

		if(dayTime > 1.0f){
			dayTime = 0.0f;
		}

		dayTime += dt / 20.0f;

		// Update 
		hm->update(dt);
		glider->update(dt);
		camera->update();
		if(lightSource->getUpdate()){
			lightSource->update(dayTime);		
		}
		printf("dt: %f, hours: %f, dayTime: %f\n",dt, hours, dayTime );
	
		// if the height map is not changing the seasons.
		if(!hm->isPause()){
			if(hours <= 24.0f){
				hours += dt * 200.0f;
			} else {
				days++;
				hours = 0.0f;
			}

			if(days >= 363){
				days = 0;
			}	
		

			// Seasons
			if(days <= months[0]+months[1]+months[2]){									// Summer

				season = months[0]+months[1]+months[2];
			
			} else if(days > season && days <= season+months[3]+months[4]+months[5]){   //Autumn
			
				season += months[3]+months[4]+months[5];
			
			} else if(days > season+months[3]+months[4]+months[5] && 
							days <= season+months[6]+months[7]+months[8]){ 				// Winter
			
				season += months[6]+months[7]+months[8];
			
			} else if(days > season+months[6] + months[7] + months[8] && 				//Spring
						days <= season+months[9] + months[10] + months[11]){		
			
				season += months[9] + months[10] + months[11];
			
			}

			hm->setDay(days);
			hm->setSeason(season);
			
		}

//    	ImGui_ImplGlfwGL3_NewFrame();
//
//    	ImGui::Text("Glider Speed: %f", glider->getSpeed());
//    	ImGui::Text("Season: %s", seasons[hm->getSeasonMode()].c_str());
//    	ImGui::Text("Day: %i", days);
//
//    	ImGui::Render();
//      ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        
		glfwSwapBuffers(window);    // SWAP BUFFERS
        glfwPollEvents();           // LISTEN FOR WINDOW EVENTS
	}

	printf("%s Closing application\n", TAG_INFO.c_str());
	glfwDestroyWindow(window);

	return 0;
}