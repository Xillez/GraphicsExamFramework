#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
 * @brief Container for functions used across application.
 */
namespace helpers{
	/**
	 * @brief Set up variables used for glfw and spawns a window for the application;
	 * @return The new window;
	 */
	GLFWwindow* glfw_setup();
	
	/**
	 * @brief Function for handling keyboard events from glfw.
	 * 
	 * @param "window" - GLFWwindow* - pointer to window where event occured.
	 * @param "key" - int - value key that was pressed.
	 * @param "scancode" - int - scancode for key that was pressed?????.
	 * @param "action" - int - where key was pressed (1) of released (0).
	 * @param "mods" - int - the mods used on event (ctrl/shift/alt).
	 */
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
}