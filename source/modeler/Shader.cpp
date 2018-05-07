#include "Shader.hpp"
#include "../helpers/errorHandler.hpp"

#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>

 GLuint modeler::Shader::id() const {
 	return shaderProgram; 
 }
modeler::Shader::Shader(const std::string path_vert_shader, const std::string path_frag_shader){

    /*-----------------------------------------------------------------------------
     *  CREATE THE SHADER
     *-----------------------------------------------------------------------------*/

	GLuint vertexShader = load_and_compile_shader(path_vert_shader, GL_VERTEX_SHADER);
	GLuint fragmentShader = load_and_compile_shader(path_frag_shader, GL_FRAGMENT_SHADER);

	// Create a program object and attach the two shaders we have compiled, the program object contains
	// both vertex and fragment shaders as well as information about uniforms and attributes common to both.
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Now that the fragment and vertex shader has been attached, we no longer need these two separate objects and should delete them.
	// The attachment to the shader program will keep them alive, as long as we keep the shaderProgram.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Link the different shaders that are bound to this program, this creates a final shader that 
	// we can use to render geometry with.
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
}

modeler::Shader::Shader(std::vector<std::pair<GLenum, std::string>> shaders){
	// shaderTypes that can be attatched
	std::vector<GLenum> available = {GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER};

	shaderProgram = glCreateProgram();

	// goes through the arguments and add each shader to the program.
	// exits if not a shader or shader is earlier in the pipeline than previosuly read.
	for (auto it = shaders.begin(); it != shaders.end(); ++it)
	{
		auto position = std::find(available.begin(), available.end(), it->first);

		if (position != available.end())
		{
			available.erase(available.begin(), position);
			GLuint programPart = load_and_compile_shader(it->second.c_str(), it->first);
			glAttachShader(shaderProgram, programPart);
			glDeleteShader(programPart);
		}
		else{
			helpers::shader_errorCallback(0, "Given shader could not be placed here in the pipeline");
			exit(-1);
		}
	}

	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
}

void modeler::Shader::bind(){ 
	glUseProgram(shaderProgram); 
}

void modeler::Shader::unbind() { 
	glUseProgram(0); 
}

GLuint modeler::Shader::load_and_compile_shader(const std::string fname, GLenum shaderType) 
{
	// Load a shader from an external file
	std::vector<char> buffer;
	read_shader_src(fname, buffer);
	const char *src = &buffer[0];

	// Create shaders
	GLuint shader = glCreateShader(shaderType);
	//attach the shader source code to the shader objec
	glShaderSource(shader, 1, &src, NULL);

	// Compile the shader
	glCompileShader(shader);
	// Comile the shader, translates into internal representation and checks for errors.
	GLint compileOK;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileOK);
	if (!compileOK) {
		char infolog[1024];
		glGetShaderInfoLog(shader, 1024, NULL, infolog);

		helpers::shader_errorCallback(0, "Could not compile shader program");
	}
	return shader;
}

void modeler::Shader::read_shader_src(const std::string fname, std::vector<char> &buffer)
{
	std::ifstream in;
	in.open(fname, std::ios::binary);

	if (!in.fail())
	{
		// Get the number of bytes stored in this file
		in.seekg(0, std::ios::end);
		size_t length = (size_t)in.tellg();

		// Go to start of the file
		in.seekg(0, std::ios::beg);

		// Read the content of the file in a buffer
		buffer.resize(length + 1);
		in.read(&buffer[0], length);
		in.close();
		// Add a valid C - string end
		buffer[length] = '\0';
	}
	else 
	{
	std::cerr << "Unable to open " << fname << " I'm out!" << std::endl;
	//std::cerr << "Unable to open " << fname << " I'm out!" << std::endl;
	exit(-1);
	}
}

std::map<std::string, GLuint> modeler::Shader::getUniform(std::map<std::string, std::string> request){
	
	std::map<std::string, GLuint> result;
	
	for (auto it = request.begin(); it != request.end(); ++it)
	{
		result.insert(std::pair<std::string, GLuint>(it->first, glGetUniformLocation(shaderProgram, it->second.c_str())));
	}

	return result;
}