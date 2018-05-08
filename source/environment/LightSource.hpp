#pragma once
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
/**
 * @brief Container for Environmental factors like light, view etc.
 */
namespace environment{

	/**
	 * @brief Light interface for shaders.
	 */
	class LightSource
	{
		public:
			/**
			 * @brief Constructs a default lightsource.
			 */
			LightSource();

			/**
			 * @brief Constructor setting all variables of the light
			 * 
			 * @param position - Lightsource position
			 * @param lightColor - Light color from the light
			 * @param attenuation - Fall off of the light through a medium.
			 */
			LightSource(glm::vec3 position, glm::vec3 lightColor, glm::vec3 attenuation, float ambientCoefficient = 0.5f, int specualarExponent = 2);

			/**
			 * @brief Deconstructer for light.
			 */
			~LightSource();

			/**
			 * @brief Updates the camera on every turn.
			 * @param dt Deltatime between frames.
			 */
			void update(float dt);

			/**
			 * @brief Getter for Attenuation for light.
			 * @return attenuation information.
			 */
			glm::vec3 getAttenuation();

			/**
			 * @brief Getter for the color data of the light.
			 * @return Light color.
			 */
			auto getColor() -> glm::vec3;

			/**
			 * @brief Getter for position of lightsource.
			 * @return World position of the lightsource.
			 */
			glm::vec3 getPosition();

			/**
			 * @brief Getter for ambient coefficient.
			 * @return coefficient.
			 */
			auto getAmbientCoefficient() -> float;

			auto getSpecularExponent() -> int;
			/**
			 * @brief Setter for lightsource position.
			 * 
			 * @param position - New world position of lightsource.
			 */
			void setPosition(glm::vec3 position);

		private:

			glm::vec3 position;			//!< Position of the lightSource.
			glm::vec3 lightColor;		//!< A color that is added to the vertex color hit by the light.
			glm::vec3 attenuation;		//!< How light decrease through a medium over distance.
			float ambientCoefficient; 	//!< Minimum light.
			int specualarExponent;		//!< Shininess.
	};
}