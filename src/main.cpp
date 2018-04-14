#include "../header/glfw_setup.hpp"
#include "../header/global_function.hpp"
#include "../header/gl_setup.hpp"
#include "../header/board.hpp"
#include "../header/camera.hpp"
//#include "../header/globalVar.hpp"
#include "../class/ShaderManager.hpp"

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
Camera* camera;
GLFWwindow* window;			//!< Default window to draw on
Board* chessBoard;
ShaderManager* shaderManager;

int main(int argc, char const *argv[])
{	
	// Ready moves for pieces
	getMoves();

	// Create camera
	//camera = new Camera(glm::vec3(1, 1, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//camera = new Camera(glm::vec3(0, 5, 0), glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));
	camera = new Camera(glm::vec3(3, 4, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//camera = new Camera(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//camera = new Camera(glm::vec3(0, 2, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	// Create common interface for shaders
	shaderManager = new ShaderManager();

	// OpenGL setup
	window = glfw_setup();
	
	// Make chessboard
	chessBoard = new Board ("../asset/modell_chessBoard.obj");

	setup_EventHandling();

	bool eh = false;
	float time = 0.0f, time2 = 0.0f, currentTime = 0.0f, lastTime = 0.0f, dt = 0.0f, animationTime = 0.0f;
	
	lastTime = glfwGetTime();
	
	// Run until close event is given to the window
	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.4, 0.8, 0.8, 1);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		currentTime = glfwGetTime();
		dt = currentTime - lastTime;

		lastTime = currentTime;

        //chessBoard->draw();
		if(animationTime > 1.0f) {
			animationTime = 1.0f;
		}
		else {
			animationTime += dt;
		}

		if (animationTime <= 1){
			std::cout << animationTime << ", " << dt << '\n';
			//chessBoard->movePiece(1, 0, 2, 2, animationTime);
			chessBoard->movePiece(0, 7, 2, 7, animationTime);
		}
		chessBoard->draw();

/*
		if(eh){
			//chessBoard->movePiece(1, 1, 1, 2);
			//chessBoard->movePiece(1, 6, 1, 5);
			chessBoard->movePiece(2, 0, 0, 2, animationTime);
        	chessBoard->draw();
			if(time2 > 8){
				chessBoard->movePiece(0, 2, 3, 5, animationTime);
        		chessBoard->draw();
			} else {
				time2 += 0.1f;
			}
			eh = false;
		}else {
			time += 0.1f;
		}
		if(time >= 3)
			eh = true;
*/

		glfwSwapBuffers(window);    //<-- SWAP BUFFERS
        glfwPollEvents();           //<-- LISTEN FOR WINDOW EVENTS

	}

	glfwDestroyWindow(window);

	return 0;
}