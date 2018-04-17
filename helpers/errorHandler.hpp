#pragma once
#include <GL/glew.h>

/**
 * @brief Container for functions used across application.
 */
namespace helpers{
	/**
	 * @brief Callback function called by glfw when error occure.
	 * 
	 * @param error Error code defined by glfw
	 * @param description Human readable description of the error.
	 */
	void glfw_errorCallback(int error, const char* description);
	
	/**
	 * @brief Callback function called when shader error occure.
	 * 
	 * @param error Error code for identifying the error.
	 * @param description Human readable description of the error.
	 */
	void shader_errorCallback(int error, const char* description);
	
	/**
	 * @brief Callback function called when assimp error occure.
	 * 
	 * @param error Error code for identifying the error.
	 * @param description Human readable description of the error.
	 */
	void assimp_errorCallback(int error, const char* description);
	
	/**
	 * @brief Callback function called when gl error occure.
	 * 
	 * @param source Where the error occured.
	 * @param type The Type of error given.
	 * @param id Identifies the error.
	 * @param severity Debug severity, notification, low, medium or high.
	 * @param length Message length.
	 * @param message Human readable description of the error.
	 * @param userParam Value set in most resent call to glDebugMessageCallback.
	 */
	void gl_errorCallback( GLenum source,
	                      GLenum type,
	                      GLuint id,
	                      GLenum severity,
	                      GLsizei length,
	                      const GLchar* message,
	                      const void* userParam );
}