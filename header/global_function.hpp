#pragma once

#include "../header/globalVar.hpp"
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

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
 *
 * @param
 * @param
 * @param
 * @param
 * @param
 */
// void onKeyboardInput();

/**
 * @brief Function to handle mouse events to window.
 *
 * @param window - GLFWwindow* - Window in context.
 * @param xpos - double - x position at time of event.
 * @param ypos - double - y position at time of event.
 */
void OnMouseMove(GLFWwindow *window, double xpos, double ypos);

/**
 * @brief Function to handle mouse events to window.
 *
 * @param
 * @param
 * @param
 * @param
 * @param
 */
// void onMouseClick(GLFWwindow* window, int button, int action, int mods);

/**
 * @brief Function to handle resume events (when game is paused and user
 * presses ESC).
 *
 * @param
 * @param
 * @param
 * @param
 * @param
 */
// void onResume();

/**
 * @brief Function to handle pause events (when game is unpaused and
 * user presses ESC).
 *
 * @param
 * @param
 * @param
 * @param
 * @param
 */
// void onPause();

/**
 * @brief Function to handle tick events (happens every frame).
 *
 * @param
 * @param
 * @param
 * @param
 * @param
 */
// void onTick();