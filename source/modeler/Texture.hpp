#pragma once

#include <GL/glew.h> 

/**
 * @brief Container for classes and structures associated with modeling consepts.
 */
namespace modeler{
    /**
     * @brief Loads and binds texture from file.
     */
    class Texture {
      public:
        GLuint TextureID;						//!< Texture identifier
    
        /**
         * @brief Getter function for the public TextureID
         * @return A Gluint defining the texture.
         */
        GLuint id() const;						//!< NOTE: remove or set TextureID to private and rename function.
        
        /**
         * @brief Loads texture based on given file path and sets the TextureID.
         * @param filename string representing the path to texturefile.
         */
        Texture(const char* filename);
    
    };
}