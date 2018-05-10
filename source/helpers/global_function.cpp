#include "global_function.hpp"
#include "../header/globalVar.hpp"
#include "../environment/Camera.hpp"	

#include <unordered_map>
#include <iostream>
#include <stdio.h>

extern GLFWwindow* window;
extern environment::Camera* camera;
bool middleMousePressed = false;

std::unordered_map<std::string, std::vector<std::string>> moves;
glm::vec2 prevMousePos(0.0f, 0.0f);

void helpers::setup_EventHandling()
{
	glfwSetCursorPosCallback(window, helpers::OnMouseMove);
	glfwSetMouseButtonCallback(window, helpers::OnMouseClick);
	glfwSetKeyCallback(window, helpers::OnKeyPress);
}

void helpers::OnMouseMove(GLFWwindow *window, double xpos, double ypos)
{
	// Calculate 2d difference in 2d (window) mouse position
	// and update last pos to be current
	glm::vec2 deltaPos(xpos - prevMousePos.x, ypos - prevMousePos.y);
	prevMousePos = {xpos,ypos};

	if (!middleMousePressed)
		return;
	
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

void helpers::OnKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS)){
    	//camera->rotateBy(0.0f, 0.1f);
    	camera->translateBy(camera->getDir());

    } else if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS)){
    	//camera->rotateBy(0.0f, -0.1f);
    	camera->translateBy(-camera->getDir());
   
    } else if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS)){
    	//camera->rotateBy(-0.1f, 0.0f);
    	camera->translateBy(glm::cross(camera->getUp(), camera->getDir()));
   
    } else if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS)){
    	//camera->rotateBy(0.1f, 0.0f);
    	camera->translateBy(glm::cross(camera->getDir(), camera->getUp()));
    }


    // TODO:

    // UP and DOWN movement.
}