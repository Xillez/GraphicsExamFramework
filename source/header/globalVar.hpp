#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "../modeler/Model.hpp"

#define COLOR_RED     "\x1b[31m"						//!< Ascii character value for color red.	
#define COLOR_GREEN   "\x1b[32m"						//!< Ascii character value for color green.	
#define COLOR_YELLOW  "\x1b[33m"						//!< Ascii character value for color yellow.	
#define COLOR_BLUE    "\x1b[34m"						//!< Ascii character value for color blue.
#define COLOR_MAGENTA "\x1b[35m"						//!< Ascii character value for color magenta.
#define COLOR_CYAN    "\x1b[36m"						//!< Ascii character value for color cyan.
#define COLOR_RESET   "\x1b[0m"							//!< Ascii character value for default color.

//! string for notating output as for debug purposes. 
const std::string TAG_DEBUG = COLOR_CYAN "[DEBUG]:\t" COLOR_RESET;
//! string for notating output as for informing user.
const std::string TAG_INFO 	= COLOR_GREEN "[INFO]:\t" COLOR_RESET;
//! string for notating output as for warning user.
const std::string TAG_WARN = COLOR_YELLOW "[WARNING]:\t" COLOR_RESET;
//! string for notating output as for informing user of errors.
const std::string TAG_ERROR = COLOR_RED "[ERROR]:\t" COLOR_RESET;	

//! Percentage size of width and hight relative to monitor.
const glm::vec2 relativeWindowSize = glm::vec2(60, 60);	 

const float PI = 3.14f;									//!< Fundamentat variables.