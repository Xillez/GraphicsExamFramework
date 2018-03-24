#include "../header/glfw_setup.hpp"
#include "../header/errorHandler.hpp"

GLFWwindow* glfw_setup(){

	//tries to initialize glfw. NOTE: should be changed to cause fatal error.
	if (!glfwInit())
	{
		glfw_errorCallback(0, "Could not initialize glfw");
		return nullptr;
	}

	glfwSetErrorCallback(glfw_errorCallback);

	// Set requiered version of opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	
	// create window
	GLFWwindow* window = glfwCreateWindow(1024, 768, "Chess-3D", nullptr, nullptr);
	
	// set window as active
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
    // Initialize GLEW QUESTION: should this be moved to other file?
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
    }
    return window;
}