#include "../header/errorHandler.hpp"
#include <GLFW/glfw3.h>

void glfw_errorCallback(int error, const char* description){

	printf("Error:\tfrom glfw with errorcode %d and description \"%s\n\"", error, description);
	
}

void shader_errorCallback(int error, const char* description){

	printf("Error: \t from shader with errorcode %d and description \"%s\n\"",error, description);
	glfwTerminate();

}

void assimp_errorCallback(int error, const char* description){

	printf("Error: \t from assimp with errorcode %d and description \"%s\n\"",error, description);

}