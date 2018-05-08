#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
 * @brief Container for Environmental factors like light, view etc.
 */
namespace environment{

	/**
	 * @brief Represent the user viewpoint.
	 */
	class Camera {
	public:
		/**
	 	* @brief Camera constructor
	 	* 
	 	* @param pos - is the position of the camera
	 	* @param target - is the focus point
	 	* @param up - is the camera upward perpective
	 	*/
		Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up);
		
		/**
		 * @brief Function for getting screen size
		 */  
		static glm::vec2 windowSize();
	
		/**
	 	* @brief Set position of camera
	 	* @param pos - new positon of camera
	 	*/
		void setPos(glm::vec3 pos);
		/**
	 	* @brief Set the focus point of camera
	 	* @param target - new direction/focus point of camera
	 	*/
		void setDir(glm::vec3 target);
		/**
	 	* @brief Set up vector of camera
	 	* @param up - new up vector of camera
	 	*/
		void setUp(glm::vec3 up);
		/**
	 	* @brief The position of camera
	 	* @return Camera position vector
	 	*/
		glm::vec3 getPos();
		/**
	 	* @brief The focus point of camera
	 	* @return Camera direction vector
	 	*/
		glm::vec3 getDir();
		/**
	 	* @brief The up of camera
	 	* @return Camera up vector
	 	*/
		glm::vec3 getUp();
	
		/**
	 	* @brief Create the camera view 
	 	* @return Camera view matrix
	 	*/
		glm::mat4 getViewMatrix();
		/**
	 	* @brief Create the perspective of camera
	 	* @return Camera perspective matrix
	 	*/
		glm::mat4 getPerspectiveMatrix();
	
		/**
		 * @brief Rotates the camera around y-axis, "angle" amount of degrees
		 * 
		 * @param angleX - value in degree to rotate camera around (0, 1, 0)
		 * @param angleY - value in degree to rotate camera around "horizontally rotated vertical rotation axis"
		 */
		void rotateBy(float angleX, float angleY);

		/**
		 * @brief [brief description]
		 * @details [long description]
		 * 
		 * @param translate [description]
		 */
		void translateBy(glm::vec3 translate);
	
	private:
		glm::vec3 pos;											//!< Position of the camera.
		glm::vec3 target;										//!< The focus point of the camera.
		float radius;											//!< Radius is distance from pos to target.
		glm::vec3 up;											//!< Normal vector from target to pos.
	
		glm::vec3 horRotAxis = glm::vec3(0.0f, 1.0f, 0.0f);		//!< Axis used for calculating sperical rotation. 
		glm::vec3 vertRotAxis = glm::vec3(1.0f, 0.0f, 0.0f);	//!< Axis used for calculating sperical rotation.
	
	};
}