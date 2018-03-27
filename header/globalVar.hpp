#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <GLFW/glfw3.h>
#include "../class/model.hpp"

GLFWwindow* window;			//!< Default window to draw on

extern Shader* shaderProgram;

extern Model* chessBoard;

extern std::unordered_map<std::string, std::vector<std::string>> moves; 	//!< move set for all the pieces
