#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "../class/model.hpp"
#include <GLFW/glfw3.h>

extern GLFWwindow* window;			//!< Default window to draw on

extern Shader* shaderProgram;

extern Model* chessBoard;

extern std::unordered_map<std::string, std::vector<std::string>> moves; 	//!< move set for all the pieces
