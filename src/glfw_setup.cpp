#include "../header/glfw_setup.hpp"
#include "../header/errorHandler.hpp"
#include <stdio.h>

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    	printf("hey\n\n");
    }
}

GLFWwindow* glfw_setup() {

	//tries to initialize glfw. NOTE: should be changed to cause fatal error.
	if (!glfwInit())
	{
		glfw_errorCallback(0, "Could not initialize glfw");
		return nullptr;
	}

	glfwSetErrorCallback(glfw_errorCallback);

	//Multisampling
	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	// Set requiered version of opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// create window
	GLFWwindow* window = glfwCreateWindow(1024, 768, "Chess-3D", nullptr, nullptr);
	glfwSetKeyCallback(window, key_callback);	
	// set window as active
	glfwMakeContextCurrent(window);

	// Number of screen updates before swapping when calling glfwSwapBuffer();
	glfwSwapInterval(1);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glewExperimental = GL_TRUE;
    // Initialize GLEW QUESTION: should this be moved to other file?
    if (glewInit() != GLEW_OK) {
    	glfw_errorCallback(0, "Could not initialize glew");
        glfwTerminate();
    }

	glEnable(GL_DEPTH_TEST);  
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glLineWidth(3); 

	// Error handeling
	glEnable( GL_DEBUG_OUTPUT );
	glDebugMessageCallback( (GLDEBUGPROC) gl_errorCallback, 0 );

    return window;
}

