#include "errorHandler.hpp"
#include "../header/globalVar.hpp"
#include <GLFW/glfw3.h>
#include <stdio.h>

void helpers::glfw_errorCallback(int error, const char* description){

	printf("%s From glfw with errorcode %d and description \"%s\n\"", TAG_ERROR.c_str(), error, description);
	
}

void helpers::shader_errorCallback(int error, const char* description){

	printf("%s From shader with errorcode %d and description \"%s\n\"", TAG_ERROR.c_str(), error, description);
	glfwTerminate();

}

void helpers::assimp_errorCallback(int error, const char* description){

	printf("%s From assimp with errorcode %d and description \"%s\n\"", TAG_ERROR.c_str(), error, description);

}

void helpers::gl_errorCallback( GLenum source,
                      GLenum type,
                      GLuint id,
                      GLenum severity,
                      GLsizei length,
                      const GLchar* message,
                      const void* userParam )
{
  printf( "%s From openGL: \n\t"
    "source = 0x%x type = 0x%x, severity = 0x%x,\n\t"
    "message = %s\n",
    TAG_INFO.c_str(), source, type, severity, message 
  );
}