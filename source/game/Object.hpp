#pragma once
#include "Piece.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <string>

/**
 * @brief Container for content specific to chess game.
 */
namespace game{
	/**
	 * @brief 8x8 chessboard managing pieces.
	 */
	class Object
	{
	public:
		
		/**
		 * @brief Board constructor.
		 */
		Object();
		
		/**
		 * @brief updates state for next frame.
		 * 
		 * @param dt - Deltatime since last frame.
		 */
		void update(float dt);

		/**
		 * @brief Draw the board and every piece found.
		 */
		void draw();
	
		/**
		 * @brief Uses bezeir curve to interpolate between three control points. 
		 * 
		 * @param a - Control point is current location.
		 * @param b - Control point is middle of point a and b.
		 * @param c - Control point is destination location.
		 * @param dt - Delta time.
		 * @return Interpolated vector between 3 points.
		 */
		//auto jumpCurve(glm::vec3 a, glm::vec3 b, glm::vec3 c, float dt) -> glm::vec3;
			
		/**
		 * @brief Uses LERP to interpolate between two control points.
		 * 
		 * @param a - Control point is current location.
		 * @param b - Control point is destination location.
		 * @param dt - Delta time.
		 * @return Interpolated vector between 2 points.
		 */
		//auto lerp(glm::vec3 a, glm::vec3 b, float dt) -> glm::vec3;
				
	private:
	
		glm::vec3 position;								//!< Origin of board.
		glm::vec3 velocity;
		glm::vec3 acceleration;
		//glm::vec3 torque;

		modeler::Shader* shaderProgram;					//!< Shaderprogram used by board for drawing.
	};
}