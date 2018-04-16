#include "../header/glfw_setup.hpp"
#include "../header/global_function.hpp"
#include "../header/gl_setup.hpp"
#include "../header/board.hpp"
#include "../header/camera.hpp"
#include "../header/globalVar.hpp"
#include "../class/ShaderManager.hpp"

#include <GLFW/glfw3.h>
#include <stdio.h>

Camera* camera;
GLFWwindow* window;			//!< Default window to draw on
Board* chessBoard;
ShaderManager* shaderManager;

int main(int argc, char const *argv[])
{	
	// Ready moves for pieces
	printf("%s: Getting moves\n",TAG_INFO.c_str());
	getMoves();

	// Create camera
	printf("%s: Setting up camera\n",TAG_INFO.c_str());
	//camera = new Camera(glm::vec3(1, 1, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//camera = new Camera(glm::vec3(0, 5, 0), glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));
	camera = new Camera(glm::vec3(0, 4, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//camera = new Camera(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//camera = new Camera(glm::vec3(0, 2, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	// Create common interface for shaders
	printf("%s Creating shadermanager\n", TAG_INFO.c_str());
	shaderManager = new ShaderManager();

	// OpenGL setup
	printf("%s Creating window\n", TAG_INFO.c_str());
	window = glfw_setup();
	
	// Make chessboard
	printf("%s Creating board\n", TAG_INFO.c_str());
	chessBoard = new Board ("../asset/modell_chessBoard.obj");

	// setup event handler
	printf("%s Setting up event handler\n", TAG_INFO.c_str());
	setup_EventHandling();

	bool eh = false;
	float time = 0.0f;
	float lastTime = glfwGetTime(); 
	// Run until close event is given to the window
	printf("%s Starting gameloop\n", TAG_INFO.c_str());
	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.4, 0.8, 0.8, 1);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		float currentTime = glfwGetTime();
		float dt = currentTime - lastTime;
		lastTime = currentTime;

		camera->rotateBy(dt, glm::vec3(0.0f, 1.0f, 0.0f));
        chessBoard->draw();

		if(eh){
			//chessBoard->movePiece(1, 1, 1, 2);
			//chessBoard->movePiece(1, 6, 1, 5);
			//chessBoard->movePiece(0, 0, 0, 4);
			//chessBoard->movePiece(2, 0, 0, 2);
			eh = false;
		}else {
			time += 0.1f;
		}
		if(time >= 3)
			eh = true;


		glfwSwapBuffers(window);    //<-- SWAP BUFFERS
        glfwPollEvents();           //<-- LISTEN FOR WINDOW EVENTS

	}

	printf("%s Closing application\n", TAG_INFO.c_str());
	glfwDestroyWindow(window);

	return 0;
}