//#include "../class/model.hpp"
#include "../header/glfw_setup.hpp"
#include "../header/global_function.hpp"
#include "../header/gl_setup.hpp"
#include "../header/board.hpp"
#include "../header/camera.hpp"
#include <GLFW/glfw3.h>
//#include "../header/globalVar.hpp"
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>

Camera* camera;
GLFWwindow* window;			//!< Default window to draw on
Board* chessBoard;


int main(int argc, char const *argv[])
{	
	// Ready moves for pieces
	getMoves();
	camera = new Camera(glm::vec3(0, 5, 0), glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));
	//camera = new Camera(glm::vec3(1, 1, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//camera = new Camera(glm::vec3(0,0,5), glm::vec3(0,0,0), glm::vec3(0,1,0));

	// OpenGL setup
	GLFWwindow* window = glfw_setup();

	// Make chessboard
	Board* chessBoard = new Board ("../asset/modell_chessBoard.obj");
	bool eh = false;
	float time = 0.0f;
	// Run until close event is given to the window
	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.4, 0.8, 0.8, 1);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		chessBoard->draw();

		if(eh){
			chessBoard->movePiece(1, 1, 2, 2);
			eh = false;
		}else {
			time += 0.1f;
		}
		if(time >= 3)
			eh = true;


		glfwSwapBuffers(window);    //<-- SWAP BUFFERS
        glfwPollEvents();           //<-- LISTEN FOR WINDOW EVENTS
	}

	glfwDestroyWindow(window);

	return 0;
}
 
