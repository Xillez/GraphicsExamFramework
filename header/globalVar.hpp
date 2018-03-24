#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <GLFW/glfw3.h>


std::unordered_map<std::string, std::vector<std::string>> moves; 	//!< move set for all the pieces

GLFWwindow* window;			//!< Default window to draw on
