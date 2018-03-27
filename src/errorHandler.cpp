#include "../header/errorHandler.hpp"
#include <GLFW/glfw3.h>
#include <stdio.h>

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

void gl_errorCallback( GLenum source,
                      GLenum type,
                      GLuint id,
                      GLenum severity,
                      GLsizei length,
                      const GLchar* message,
                      const void* userParam )
{
  printf( "Eroor: \t from openGL source = 0x%x type = 0x%x, severity = 0x%x, message = %s\n",
            source, type, severity, message );
}