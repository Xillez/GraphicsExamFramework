#pragma once

#include <GL/glew.h>
#include <vector>
#include <map>

/**
 * @brief Container for classes and structures associated with modeling consepts. 
 */
namespace modeler{
      /**
       * @brief Represent a GL shader program
       */
      class Shader {
      
            public:
                  GLuint shaderProgram;               //!< identifier for the shader program

                  /**
                  * @brief getter for shderProgram.
                  * @return shaderProgram id.
                  */
                  GLuint id() const;
                  
                  /** \deprecated
                   * @brief constructs a shader out of a vertex shader and fragment shader.
                   * 
                   * @param path_vert_shader - File path to the vertex shader.
                   * @param path_frag_shader - File path to the frag shader.
                   */
                  Shader(const std::string path_vert_shader, const std::string path_frag_shader);
                  /**
                   * @brief Create a shaderprogram based on pairs of shadertype and filepath 
                   * @details The shaders in the vector should be ordered like the glpipeline
                   * 
                   * @param shaders - Pair of GLenum shaderType and filepath string.
                   */
                  Shader(std::vector<std::pair<GLenum, std::string>> shaders);
                  
                  /**
                   * @brief runs glUseProgram on the shader.
                   */
                  void bind();
      
                  /**
                   * @brief Unbinds all shaders.
                   */
                  void unbind();
                  
                  /**
                   * @brief Loads and compiles a shader based on given name and type. 
                   * 
                   * @param fname Directory path to shader.
                   * @param shaderType GL shader type to compile.
                   * 
                   * @return identifier for the shader.
                   */
                  GLuint load_and_compile_shader(const  std::string fname, GLenum shaderType);
                  
                  
                  /**
                   * @brief Reads file from given filepath.
                   * 
                   * @param fname filepath of the shader.
                   * @param buffer Where the file is stored.
                   */
                  void read_shader_src(const  std::string fname, std::vector<char> &buffer);
      
                  /**
                   * @brief gets the requested uniform values from the shader 
                   * 
                   * @param request map of names to return as and name of uniforms as named in shader.
                   * @return map of names specified in request and uniformloaction requested.
                   */
                  std::map<std::string, GLuint> getUniform(std::map<std::string, std::string> request);
      };
}