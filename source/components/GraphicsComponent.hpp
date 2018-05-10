#pragma once

#include "../modeler/Shader.hpp"
#include "../modeler/Model.hpp"
#include "IComponent.hpp"

/**
 * @brief Container for classes and structures associated with components. 
 */
namespace components
{
	/**
	 * @brief Interface class for components.
	 */
	class GraphicsComponent : public IComponent
	{	
		protected: 
			modeler::Model* model = nullptr;
			std::string path;
			
		public:
			/**
			 * @brief Interface component class constructor.
			 */
			GraphicsComponent(std::string const &modelPath);

			/**
			 * @brief initialize function to give component parent object for updating and possibly drawing.
			 * 
			 * @param parent - Parent object I exists inside.
			 */
			auto init(game::Object* parent) -> void;

			/**
			 * @brief Update function for components. 
			 */
			auto update(float dt) -> void;
	
			/**
			 * @brief Draw the mesh on the screen using given shader program.
			 * @param shader A shader program for GL pipeline.
			 */
			auto draw() -> void;

			auto getType() -> int;
	};
}
