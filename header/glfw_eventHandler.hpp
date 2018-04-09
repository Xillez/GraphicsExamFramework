#pragma once

#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

// TODO: Make eventhandler handler click and find correct piece and call 

class EventHandler
{
	public:
		/**
		 * @brief Constructor for EventHandler class. Takes in the window and some map stuff.
		 */
		EventHandler();

		/**
		 * @brief Function for setup of eventhandling callback functions.
		 * 
		 * @param window - GLFWwindow* - The pointer to the current window.
		 */
		void setup_eventHandler(GLFWwindow* window);

    private:
		/**
		 * @brief Function to handle keyboard events sent to window.
		 *
		 * @param
		 * @param
		 * @param
		 * @param
		 * @param
		 */
        //void onKeyboardInput();

        /**
         * @brief Function to handle mouse events to window.
         *
         * @param
         * @param
         * @param
         * @param
         * @param
         */
        void onMouseMove(GLFWwindow* window, double xpos, double ypos);

        /**
		 * @brief Function to handle mouse events to window.
		 *
		 * @param
		 * @param
		 * @param
		 * @param
		 * @param
		 */
		void onMouseClick(GLFWwindow* window, int button, int action, int mods);

        /**
		 * @brief Function to handle resume events (when game is paused and user presses ESC).
		 *
		 * @param
		 * @param
		 * @param
		 * @param
		 * @param
		 */
        //void onResume();

        /**
		 * @brief Function to handle pause events (when game is unpaused and user presses ESC).
		 *
		 * @param
		 * @param
		 * @param
		 * @param
		 * @param
		 */
        //void onPause();

        /**
		 * @brief Function to handle tick events (happens every frame).
		 *
		 * @param
		 * @param
		 * @param
		 * @param
		 * @param
		 */
        //void onTick();

		GLFWwindow* window;	//!< Local pointer to window
};