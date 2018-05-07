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

		public:
			/**
			 * @brief Interface component class constructor.
			 */
			GraphicsComponent(std::string const &modelPath);

			/**
			 * @brief Update function for components. 
			 */
			virtual auto update(float dt) -> void;
	
			/**
			 * @brief Draw the mesh on the screen using given shader program.
			 * @param shader A shader program for GL pipeline.
			 */
			virtual auto draw(modeler::Shader shader) -> void;

			virtual auto getType() -> int;
	};
}
