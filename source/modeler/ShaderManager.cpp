#include "ShaderManager.hpp"

#include <functional>
#include <algorithm>

modeler::ShaderManager::ShaderManager(){

}

modeler::ShaderManager::~ShaderManager(){
	//TODO: Delete all shaders.
}

modeler::Shader* modeler::ShaderManager::getShader(std::vector<std::pair<GLenum, std::string>> shaders){
	
	std::string shaderName;										//Concatination of all shader paths
	
	// Concatenate the paths
	for (auto it = shaders.begin(); it != shaders.end(); ++it)
	{
		shaderName.append(it->second);
	} 


	std::size_t shaderHash = std::hash<std::string>{}(shaderName);	// Hash of the concatenated shadername

	// Find requested shader if it exists
	auto it = std::find_if( 
		shaderList.begin(), shaderList.end(),
    	[shaderHash](std::pair<std::size_t, Shader*>& touple){
    		return touple.first == shaderHash;
    	}
    );


	// set return value to the found shader
	if(it != shaderList.end()){
		Shader* shader = it->second;
		return shader;
	}
	else{	// Shader was not found and creates it.
		Shader* shader = new Shader(shaders);
		shaderList.push_back(std::pair<std::size_t,  Shader*>(shaderHash, shader));

		return shader;
	}
}
