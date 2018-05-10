#pragma once

#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

/**
 * @brief Container for functions used across application.
 */
namespace helpers{ 
	/**
	 * @brief Process the file data and fetch the moves set for every piece.
	 * @details The function follows the file structure to fetch the data.
	 */
	void getMoves();
	
	/**
	 * @brief Function for setup of eventhandling callback functions.
	 */
	void setup_EventHandling();
	
	/**
	 * @brief Function to handle keyboard events sent to window.
	 */
	void onKeyboardInput();
	
	/**
	 * @brief Function to handle mouse events to window.
	 * 
	 * @param window - Window in context.
	 * @param xpos - x position at time of event.
	 * @param ypos - y position at time of event.
	 */
	void OnMouseMove(GLFWwindow *window, double xpos, double ypos);
	
	/**
	 * @brief Function to handle mouse events to window.
	 * 
	 * @param window - pointer to window event occured in
	 * @param button - button that was pressed within event
	 * @param action - action user performed on button (pressed, released)
	 * @param mods - modifiers that was pressed within event (ctrl, shift, alt etc.)
	 */
	void OnMouseClick(GLFWwindow* window, int button, int action, int mods);
	
	/**
	 * @brief Function to convert window mouse position to OpenGl world position
	 * 
	 * @param xpos - X position of mouse
	 * @param ypos - Y position of mouse
	 */
	glm::vec3 convertMousePosToWorld(double xpos, double ypos);

	/**
	 * @brief Function to handle key events to window.
	 * @details [long description]
	 * 
	 * @param window - pointer to window event occured in.
	 * @param key - Key that was pressed winith event.
	 * @param scancode - System specific scancode of key.
	 * @param action - Action user performed on key (pressed, released)
	 * @param mods - Bit field describing which modifier keys were held down.
	 */
	void OnKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);


}