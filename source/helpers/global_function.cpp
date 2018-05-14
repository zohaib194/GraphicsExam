#include "global_function.hpp"
#include "../game/Glider.hpp"
#include "../game/HeightMap.hpp"
#include "../header/globalVar.hpp"
#include "../environment/Camera.hpp"	

#include <unordered_map>
#include <iostream>
#include <stdio.h>
#include <random>

extern GLFWwindow* window;
extern environment::Camera* camera;
extern game::HeightMap* hm;
extern game::Glider* glider;
bool middleMousePressed = false;
glm::vec2 prevMousePos(0.0f, 0.0f);

void helpers::setup_EventHandling()
{
	glfwSetCursorPosCallback(window, helpers::OnMouseMove);
	glfwSetMouseButtonCallback(window, helpers::OnMouseClick);
	glfwSetKeyCallback(window, helpers::OnKeyPress);
}

void helpers::OnMouseMove(GLFWwindow *window, double xpos, double ypos)
{
	// if the Camera is following then return
	if(camera->getFollow()){
		return;
	}
	// Calculate 2d difference in 2d (window) mouse position
	// and update last pos to be current
	glm::vec2 deltaPos(xpos - prevMousePos.x, ypos - prevMousePos.y);
	prevMousePos = {xpos,ypos};
/*
	if (!middleMousePressed)
		return;
	*/
	// Rotate camera around both rotational axes
	camera->rotateBy(-deltaPos.x / 100.0f, (deltaPos.y * -1) / 100.f);
}

void helpers::OnMouseClick(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		glm::vec3 pointerPos = convertMousePosToWorld(xpos, ypos);
	}
	else if (button == GLFW_MOUSE_BUTTON_2 && action == GLFW_PRESS)
	{
		middleMousePressed = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_2 && action == GLFW_RELEASE)
	{
		middleMousePressed = false;
	}
}

glm::vec3 helpers::convertMousePosToWorld(double xpos, double ypos)
{
	// Get window size.
	glm::vec2 wSize = environment::Camera::windowSize();
    GLfloat viewportY, z;

	// Flip y axis to see where we are in viewport's y.
    viewportY = wSize.y - ypos;

	// Get the z-axis value that generated this pixel.
    glReadPixels(xpos, viewportY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	// Assemble were we were inside viewport with z depth.
    glm::vec3 mousePosInViewport = glm::vec3(xpos, viewportY, z);

	// Get the view and projection matrix form camera.
    glm::mat4 viewMatrix = camera->getViewMatrix();
    glm::mat4 projectionMatrix = camera->getPerspectiveMatrix();

	// Unproject the view and projection, based on the viewport and get the position within the world.
	return glm::unProject(mousePosInViewport, viewMatrix, projectionMatrix,
		glm::vec4(0.0f, 0.0f, wSize.x, wSize.y));
}

void helpers::OnKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_I && (action == GLFW_REPEAT || action == GLFW_PRESS)){
    	//camera->rotateBy(0.0f, 0.1f);
    	camera->translateBy(camera->getDir());

    } else if (key == GLFW_KEY_K && (action == GLFW_REPEAT || action == GLFW_PRESS)){
    	//camera->rotateBy(0.0f, -0.1f);
    	camera->translateBy(-camera->getDir());
   
    } else if (key == GLFW_KEY_J && (action == GLFW_REPEAT || action == GLFW_PRESS)){		// Left
    	//camera->rotateBy(-0.1f, 0.0f);
    	camera->translateBy(glm::cross(camera->getUp(), camera->getDir()));
   
    } else if (key == GLFW_KEY_L && (action == GLFW_REPEAT || action == GLFW_PRESS)){
    	//camera->rotateBy(0.1f, 0.0f);
    	camera->translateBy(glm::cross(camera->getDir(), camera->getUp()));
    } else if (key == GLFW_KEY_Y && (action == GLFW_REPEAT || action == GLFW_PRESS)){
    	camera->translateBy(camera->getUp());

    } else if (key == GLFW_KEY_H && (action == GLFW_REPEAT || action == GLFW_PRESS)){
    	camera->translateBy(-camera->getUp());

    } else if (key == GLFW_KEY_N && (action == GLFW_REPEAT || action == GLFW_PRESS)){		// Zooming in N
    	camera->setZoom(0.1f);
    } else if (key == GLFW_KEY_M && (action == GLFW_REPEAT || action == GLFW_PRESS)){		// Zooming out M
    	camera->setZoom(-0.1f);
    } else if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS)){		// Direct glider to -z
    	glider->setOrientation(glm::vec3(0.0f, 0.0f, -1.0f), glm::radians(1.0f));
    } else if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS)){		// Direct glider to y
    	glider->setOrientation(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(1.0f));
    } else if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS)){		// Direct glider to z
    	glider->setOrientation(glm::vec3(0.0f, 0.0f, 1.0f), glm::radians(1.0f));
    } else if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS)){		// Direct glider to -y
    	glider->setOrientation(glm::vec3(0.0f, -1.0f, 0.0f), glm::radians(1.0f));
    } else if (key == GLFW_KEY_COMMA && (action == GLFW_REPEAT || action == GLFW_PRESS)){	// Increase speed of glider
    	glider->addOnSpeed(0.1);
    } else if (key == GLFW_KEY_PERIOD && (action == GLFW_REPEAT || action == GLFW_PRESS)){	// Decrease speed of glider
    	glider->subFromSpeed(0.1);
    } else if (key == GLFW_KEY_SLASH && (action == GLFW_REPEAT || action == GLFW_PRESS)){							// Camera follow the glider in 3rd person perspective.
    	
		// if the Camera is following then return
		if(!camera->getFollow()){
    		camera->followGlider(true);
		} else {
    		camera->followGlider(false);
		}

    } else if (key == GLFW_KEY_F && (action == GLFW_REPEAT || action == GLFW_PRESS)){		// Respawn glider to a random position in terrain.
    	// Random generator and device.
    	std::random_device randomDevice;
		std::default_random_engine randomGenerator(randomDevice());
		std::uniform_real_distribution<float> randomX(0.0f, hm->getWidthHeight().first / 2.0f);
		std::uniform_real_distribution<float> randomY(100.0f, 150.0f);
		std::uniform_real_distribution<float> randomZ(0.0f, hm->getWidthHeight().second / 2.0f);
		glm::vec3 randomPos = glm::vec3(
										randomX(randomGenerator), 
										randomY(randomGenerator), 
										randomZ(randomGenerator)
										);
   
    	glider->respawn(glm::vec3(randomPos.x, randomPos.y, randomPos.z));   
    } else if ((key == GLFW_KEY_R && (action == GLFW_REPEAT || action == GLFW_PRESS))){		// Reset glider to its previous position.
    	glider->resetToPrevPosition();
    } else if ((key == GLFW_KEY_O && (action == GLFW_REPEAT || action == GLFW_PRESS))){		// Contour lines.
    	if(!hm->getContour()){
    		hm->setContour(true);
    	} else {
    		hm->setContour(false);
    	}
    } else if ((key == GLFW_KEY_5 && (action == GLFW_REPEAT || action == GLFW_PRESS))){		// Seasons change
    	if(!hm->isPause()){
    		hm->pauseSeasons(true);
    	} else {
    		hm->pauseSeasons(false);
    	}
    } else if ((key == GLFW_KEY_1 && (action == GLFW_REPEAT || action == GLFW_PRESS))){		// Spring
		hm->pauseSeasons(true);
		hm->setSeasonMode(0);
		hm->setDay(90);
		hm->setSeason(months[0]+months[1]+months[2]);
    } else if ((key == GLFW_KEY_2 && (action == GLFW_REPEAT || action == GLFW_PRESS))){		// Summer
		hm->pauseSeasons(true);
    	hm->setSeasonMode(1);
    	hm->setDay(181);
		hm->setSeason(months[0]+months[1]+months[2]+months[3]+months[4]+months[5]);			
    } else if ((key == GLFW_KEY_3 && (action == GLFW_REPEAT || action == GLFW_PRESS))){		// Autumn
		hm->pauseSeasons(true);
    	hm->setSeasonMode(2);
    	hm->setDay(273);
    	hm->setSeason(	months[0] + months[1] + months[2] + months[3] + months[4] +			
						months[5] +	months[6] + months[7] + months[8] - 1
					);
    } else if ((key == GLFW_KEY_4 && (action == GLFW_REPEAT || action == GLFW_PRESS))){		// Winter
		hm->pauseSeasons(true);
    	hm->setSeasonMode(3);
    	hm->setDay(363);
		hm->setSeason(	months[0] + months[1] + months[2] + months[3] + months[4] +				
						months[5] +	months[6] + months[7] + months[8] + months[9] + months[10] + months[11] - 2);
				
    }  else if ((key == GLFW_KEY_6 && (action == GLFW_REPEAT || action == GLFW_PRESS))){		// Contour lines.
    	
    }
}