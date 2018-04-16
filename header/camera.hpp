#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
	/**
 	* @brief Camera constructor
 	* 
 	* @param pos is the position of the camera
 	* @param target is the focus point
 	* @param up is the camera upward perpective
 	*/
	Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up);
	/**
 	* @brief set position of camera
 	* @param pos new positon of camera
 	*/
	void setPos(glm::vec3 pos);
	/**
 	* @brief set the focus point of camera
 	* @param target new direction/focus point of camera
 	*/
	void setDir(glm::vec3 target);
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

	/**
	 * @brief rotates the camera around y-axis, "angle" amount of degrees
	 * 
	 * @param "angleX" - float - value in degree to rotate camera around (0, 1, 0)
	 * @param "angleY" - float - value in degree to rotate camera around "horizontally rotated vertical rotation axis"
	 */
	void rotateBy(float angleX, float angleY);

private:
	glm::vec3 pos;
	glm::vec3 target;
	float radius;
	glm::vec3 up;

	glm::vec3 horRotAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 vertRotAxis = glm::vec3(1.0f, 0.0f, 0.0f);

};