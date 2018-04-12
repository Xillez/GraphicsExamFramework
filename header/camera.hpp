#pragma once
#include "globalVar.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
	/**
 	* @brief Camera constructor
 	* @details [long description]
 	* 
 	* @param pos is the position of the camera
 	* @param dir is the focus point
 	* @param up is the camera upward perpective
 	*/
	Camera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up);
	/**
 	* @brief set position of camera
 	* @param pos new positon of camera
 	*/
	void setPos(glm::vec3 pos);
	/**
 	* @brief set the focus point of camera
 	* @param dir new direction/focus point of camera
 	*/
	void setDir(glm::vec3 dir);
	/**
 	* @brief set up vector of camera
 	* @param up new up vector of camera
 	*/
	void setUp(glm::vec3 up);
	/**
 	* @brief the position of camera
 	* @return camera position vector
 	*/
	glm::vec3 getPos();
	/**
 	* @brief the focus point of camera
 	* @return camera direction vector
 	*/
	glm::vec3 getDir();
	/**
 	* @brief the up of camera
 	* @return camera up vector
 	*/
	glm::vec3 getUp();

	/**
 	* @brief create the camera view 
 	* @return camera view matrix
 	*/
	glm::mat4 getViewMatrix();
	/**
 	* @brief create the perspective of camera
 	* @return camera perspective matrix
 	*/
	glm::mat4 getPerspectiveMatrix();

private:
	glm::vec3 pos;
	glm::vec3 dir;
	glm::vec3 up;

};