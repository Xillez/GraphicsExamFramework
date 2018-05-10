#include "../helpers/glfw_setup.hpp"
#include "../helpers/global_function.hpp"
#include "../game/Object.hpp"
#include "../modeler/Renderer.hpp"
#include "../components/GraphicsComponent.hpp"
#include "../environment/Camera.hpp"
#include "../environment/LightSource.hpp"
#include "../header/globalVar.hpp"
#include "../modeler/ShaderManager.hpp"

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>

modeler::ShaderManager* shaderManager;
modeler::Renderer* render;
environment::Camera* camera;
environment::LightSource* lightSource;
GLFWwindow* window;
game::Object* cube[2];

int main(int argc, char const *argv[])
{	
	// Ready moves for pieces
	printf("%s Getting moves\n",TAG_INFO.c_str());

	// Create camera
	printf("%s Setting up camera\n",TAG_INFO.c_str());
	camera = new environment::Camera(glm::vec3(0, 0, 5), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

	// Setting up light
	printf("%s Setting up LightSource\n",TAG_INFO.c_str());
	lightSource = new environment::LightSource();

	// Create common interface for shaders
	printf("%s Creating shadermanager\n", TAG_INFO.c_str());
	shaderManager = new modeler::ShaderManager();

	// OpenGL setup
	printf("%s Creating window\n", TAG_INFO.c_str());
	window = helpers::glfw_setup();

		// Create renderer.
	printf("%s Creating renderer\n", TAG_INFO.c_str());
	render = new modeler::Renderer();
	
	// Make graphics component for "cube
	components::GraphicsComponent* component = new components::GraphicsComponent("../asset/resources/nanosuit.obj");
	components::GraphicsComponent* component2 = new components::GraphicsComponent("../asset/basic_cube.obj");

	// Make cube
	printf("%s Creating board\n", TAG_INFO.c_str());
	cube[0] = new game::Object();
	cube[1] = new game::Object();
	cube[0]->registerComponent(component);
	cube[1]->registerComponent(component2);
	component = nullptr;

	render->createVAOVBO();

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

		cube[0]->draw(dt);
		cube[1]->setPos(glm::vec3(.0f, 0.0f, 0.0f));
		cube[1]->draw(dt);

        printf("\n\n\n\n");
	
		glfwSwapBuffers(window);    // SWAP BUFFERS
        glfwPollEvents();           // LISTEN FOR WINDOW EVENTS

	}

	printf("%s Closing application\n", TAG_INFO.c_str());
	glfwDestroyWindow(window);

	return 0;
}