#pragma once

#include <GLFW/glfw3.h>

class EventHandler
{
    public:
		/**
		 * @brief Function to handle keyboard events sent to window.
		 *
		 * @param
		 * @param
		 * @param
		 * @param
		 * @param
		 */
        void onKeyboardInput();

        /**
         * @brief Function to handle mouse events to window.
         *
         * @param
         * @param
         * @param
         * @param
         * @param
         */
        void onMouseInput();

        /**
		 * @brief Function to handle resume events (when game is paused and user presses ESC).
		 *
		 * @param
		 * @param
		 * @param
		 * @param
		 * @param
		 */
        void onResume();

        /**
		 * @brief Function to handle pause events (when game is unpaused and user presses ESC).
		 *
		 * @param
		 * @param
		 * @param
		 * @param
		 * @param
		 */
        void onPause();

        /**
		 * @brief Function to handle tick events (happens every frame).
		 *
		 * @param
		 * @param
		 * @param
		 * @param
		 * @param
		 */
        void onTick();
    protected:
        //
    private:
        
};
