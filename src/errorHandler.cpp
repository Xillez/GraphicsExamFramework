#include "../header/errorHandler.hpp"

void glfw_errorCallback(int error, const char* description){

	printf("Error:\tfrom glfw with errorcode %d and description \"%s\n\"", error, description);
	
}