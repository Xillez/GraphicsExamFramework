#include <stdio.h>

/**
 * @brief Callback function called by glfw when error occure.
 * 
 * @param error Error code defined by glfw
 * @param description Human readable description of the error.
 */
void glfw_errorCallback(int error, const char* description);

/**
 * @brief Callback function called when shader error occure.
 * 
 * @param error Error code for identifying the error.
 * @param description Human readable description of the error.
 */
void shader_errorCallback(int error, const char* description);

/**
 * @brief Callback function called when assimp error occure.
 * 
 * @param error Error code for identifying the error.
 * @param description Human readable description of the error.
 */
void assimp_errorCallback(int error, const char* description);