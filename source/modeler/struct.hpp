#pragma once

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

/**
 * @brief Container for classes and structures associated with modeling consepts.
 */
namespace modeler{
	/**
	 * @brief Vertex array object for interfacing with OpenGL
	 */
	struct VAO {
		GLuint VertexArrayID;	//!< Id of bound OpenGL VAO.
		GLuint VertexBuffer;	//!< Id of bound OpenGL VBO position data.
		GLuint ColorBuffer;		//!< Id of bound OpenGL VBO containing color data.
		GLuint TextureBuffer;	//!< Id of bound OpenGL VBO containing texture position.
		GLuint TextureID;		//!< Id of texture associated to texture buffer.
		GLuint ElementBuffer;	//!< Id of bound OpenGL EBO.
		GLuint NormalBuffer;	//!< Id of bound OpenGL VBO for normal data.
	
		GLenum PrimitiveMode; 	//!< Information for OpenGL primitive to draw.
		GLenum FillMode; 		//!< Information for coloring of shape.
		int NumVertices;		//!< Number of verticies in the VAO.
	};
	
	/**
	 * @brief Position data with attributes for drawing primitives.
	 */
	struct Vertex {
		
		glm::vec3 Position;		//!< Spacial position in OpenGL.
		glm::vec3 Normal;		//!< Vector perpendicular to the face the Vertex is part of.
		glm::vec2 TexCoords;	//!< Where the vertex is mapped to the texture.
		glm::vec3 Tangent;		//!< Information usefull for lighting.	
		glm::vec3 Bitangent;	//!< Information usefull for defining curves.
	};
	
	/**
	 * @brief texture loaded from file.
	 */
	struct TextureA {
		unsigned int id;		//!< Identifier for the texture.
		std::string type;		//!< The type of data given by the texure. (color, hight, etc)
		std::string path;		//!< File path to the texture.
	};
}