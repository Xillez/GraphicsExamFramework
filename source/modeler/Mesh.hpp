#pragma once

#include "struct.hpp"
#include "Shader.hpp"

#include <vector>

/**
 * @brief Container for classes and structures associated with modeling consepts. 
 */
namespace modeler{
	/**
	 * @brief Collection of vertices, geometry and topology for part a model.
	 */
	class Mesh {
	
		public:
			std::vector<Vertex> vertices;		//!< Collection of position data and optional attributes.
			std::vector<unsigned int> indices; 	//!< Relative connection of vertices to define a face/surface.
			std::vector<TextureA> textures;		//!< Texture information for mapping to vertices.
			unsigned int VAO;					//!< Vertex array object associated with the mesh. NOTE: VAO  should be associate with multiple meshes.
	
			/**
			 * @brief gets the vertex, indeci and texture data. Generates a VAO.
			 * @param vertices vector of attributes to beributes associated with the mesh.
			 * @param indices vector for connection of vertices to define a face/surface.
			 * @param textures A vector of loaded textures.
			 */
			Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureA> textures);
	
			/**
			 * @brief Draw the mesh on the screen using given shader program.
			 * @param shader A shader program for GL pipeline.
			 */
			void Draw(Shader shader);
	
		private:
			unsigned int VBO; //!< Vertex buffer object for drawing 
			unsigned int EBO; //!< Vertex element buffer for drawing
	
			/**
			 * @brief Creates VAO, VBO and EBO for the given mesh.
			 */
			void createVAOVBO();
	};
}