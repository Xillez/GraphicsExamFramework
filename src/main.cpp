#include "../class/model.hpp"
#include "../header/glfw_setup.hpp"
#include "../header/global_function.hpp"
#include "../header/gl_setup.hpp"
#include "../header/piece.hpp"
#include "../header/globalVar.hpp"
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>


int main(int argc, char const *argv[])
{	


	getMoves();

	// OpenGL setup
	GLFWwindow* window = glfw_setup();

	Board* chessBoard = new Board ("../asset/modell_chessBoard.obj");
	
	
	while(!glfwWindowShouldClose(window)) {

		glClearColor(0.0,0.0,0.0,1);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		chessBoard->draw();


		glfwSwapBuffers(window);    //<-- SWAP BUFFERS
        glfwPollEvents();           //<-- LISTEN FOR WINDOW EVENTS
	}
	glfwDestroyWindow(window);


	return 0;
}
 
