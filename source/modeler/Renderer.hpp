#pragma once

#include "struct.hpp"
#include "Shader.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace modeler
{
    class Renderer
    {
        public:
            auto registerModel(std::string path) -> std::pair<int, int>;
            auto draw(Shader shader, std::pair<int, int> vao_vbo, glm::mat4 model) -> void;

        protected:
            auto readModel(std::string path) -> void;

            std::unordered_map<std::string, std::pair<int, std::pair<int, int>>> map;
            int lastVAO = 0;
            int lastVBO = 0;

			GLuint VAO;	//!< Vertex array object associated with the mesh. NOTE: VAO  should be associate with multiple meshes.
			GLuint VBO; //!< Vertex buffer object for drawing 
			GLuint EBO; //!< Vertex element buffer for drawing

			std::vector<Vertex> vertices;		//!< Collection of position data and optional attributes.
			std::vector<unsigned int> indices; 	//!< Relative connection of vertices to define a face/surface.
			std::vector<TextureA> textures;		//!< Texture information for mapping to vertices.
	
			/**
			 * @brief Creates VAO, VBO and EBO for the given mesh.
			 */
			void createVAOVBO();
    };
}