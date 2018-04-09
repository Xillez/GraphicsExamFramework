#pragma once

#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

class EventInterface
{
	public:
		/**
		 * @brief Constructor for EventInterface class.
		 */
		EventInterface();

    private:
		/**
		 * @brief Function to handle keyboard events from window.
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
        virtual void onMouseMove(GLFWwindow* window, double xpos, double ypos) = 0;

        /**
		 * @brief Function to handle mouse events to window.
		 *
		 * @param
		 * @param
		 * @param
		 * @param
		 * @param
		 */
		virtual void onMouseClick(GLFWwindow* window, int button, int action, int mods) = 0;

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


/*class GameObect
{
	public:
		virtual void onUpdate() = 0;
};

#define EVENT_UPDATE 0x01

typedef void(*OnUpdate)();

void regEventCALLBACK(int event, GameObect callbackobj, OnUpdate);

void regCallback(int event, OnUpdate func);*/