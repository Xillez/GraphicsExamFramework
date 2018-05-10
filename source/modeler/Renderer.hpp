#pragma once

#include "struct.hpp"
#include "Shader.hpp"
#include "../game/Object.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace modeler
{
    class Renderer
    {
        public:
        	Renderer();
        	~Renderer();
            auto registerModel(std::string path) -> void;
            auto draw(std::string path, game::Object* object) -> void;

        protected:
            auto loadModel(std::string path) -> void;

            Shader* shaderProgram;					//!< Shaderprogram used by board for drawing.

            std::unordered_map<std::string, std::pair<int, std::pair<int, int>>> map;
            int lastVAO = 0;
            int lastVBO = 0;

            std::vector<GLuint> VAO;
            std::vector<GLuint> BO;

			

			std::vector<std::string> modelPath;
			std::vector<Mesh> meshes;		//!< Collection of position data and optional attributes.
			std::vector<Vertex> vertices;		//!< Collection of position data and optional attributes.
			std::vector<unsigned int> indices; 	//!< Relative connection of vertices to define a face/surface.
			std::vector<TextureA> textures;		//!< Texture information for mapping to vertices.
	
			/**
			 * @brief Creates VAO, VBO and EBO for the given mesh.
			 */
			void createVAOVBO();
    };
}