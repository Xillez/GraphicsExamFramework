#pragma once

#include "Shader.hpp"

#include <string>

/**
 * @brief Container for classes and structures associated with modeling consepts.
 */
namespace modeler{
	/**
	 * @brief Manages shaders as resources.
	 */
	class ShaderManager{
		public:
			/**
			 * @brief Get an instanse for managing a set of shaders.
			 */
			ShaderManager();
	
			/**
			 * @brief Deletes all shaders generated with the shadermanager.
			 */
			~ShaderManager();
	
			/**
			 * @brief gets shader or constructs it if it has not been made yes not exist yet.
			 * @details Creates a hash based on the combined filepasths and
			 * search for the hash in shaderList. If it is not found, it calls Shader constructor
			 * with shaders parameter.
			 * 
			 * @param shaders vector of pairs where first value is type of shader and second value is filepath for the shader.
			 * @return Requested shader if it can be created.
			 */
			Shader* getShader(std::vector<std::pair<GLenum, std::string>> shaders);
	
		private:
			//! vector of pairs where first value is filepath hash and second value is the resulting shader program.
			std::vector<std::pair<std::size_t,  Shader*>> shaderList;		
	};
}