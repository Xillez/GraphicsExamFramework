#pragma once
#include "../modeler/Model.hpp"
#include <glm/glm.hpp>

#include <vector>
#include <string>
namespace game{

	class Cube : modeler::Model{
	public:
		
		Cube(std::string const &path);
		
		~Cube();

		/**
		 * @brief Draw the cube.
		 */
		void draw();

	private:
		glm::vec3 position;								//!< Origin of board.
		modeler::Shader* shaderProgram;					//!< Shaderprogram used by board for drawing.
	};
}