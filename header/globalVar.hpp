#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "../class/model.hpp"

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

const std::string TAG_DEBUG = COLOR_CYAN "[DEBUG]:\t" COLOR_RESET;
const std::string TAG_INFO 	= COLOR_GREEN "[INFO]:\t" COLOR_RESET;
const std::string TAG_ERROR = COLOR_RED "[ERROR]:\t" COLOR_RESET;

const glm::vec2 relativeWindowSize = glm::vec2(60, 60);     //!< percentage size of width and hight relative to monitor. 

const float PI = 3.14f;

//extern Shader* shaderProgram;



//Camera* camera = new Camera(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));