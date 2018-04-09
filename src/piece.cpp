#include "../header/piece.hpp"
#include "../header/globalVar.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


Piece::Piece(std::string const &path, std::string const &pieceName, bool isWhite) : Model(path){

	std::unordered_map<std::string, std::vector<std::string>>::iterator found = moves.find(pieceName);

	if(found == moves.end()){
		std::cout << "There are no moves for a piece called " << pieceName << '\n';
	}
	else {
		/*for(auto v : found->second){
			move.push_back(v);
		}*/
		this->move = found->second;
	}
	this->isWhite = isWhite;
	this->shaderProgram = new Shader("../shader/vertexPiece.vert", "../shader/fragmentPiece.frag");
	this->shaderProgram->bind();
}


void Piece::draw(){
	static float time = 0.0;
	time += .01;
	//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 projection = glm::perspective(3.14f / 3.0f, (GLfloat)1024 / (GLfloat)768, 0.1f, -10.0f);
	std::map<std::string, GLuint> uniforms = shaderProgram->getUniform(	std::map<std::string, GLchar*>({
		{"viewID", "view"},
		{"projectionID", "projection"},
		{"modelID", "model"},
		{"normalMatrixID", "normalMatrix"},
		{"colorID", "color"},
	}));

	glUniformMatrix4fv(uniforms["viewID"], 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(uniforms["projectionID"], 1, GL_FALSE, glm::value_ptr(projection));
	glm::mat4 modelm;

	modelm = glm::translate(modelm, glm::vec3(x, y, z)); // translate it down so it's at the center of the scene
	modelm = glm::scale(modelm, glm::vec3(0.015f, 0.015f, 0.015f));	// it's a bit too big for our scene, so scale it down
															//glm::mat4 model = glm::rotate(glm::mat4(), time, glm::vec3(0, 1, 0));
	//modelm = glm::rotate(modelm, time, glm::vec3(0, 1, 0));														//ourShader.setMat4("model", model);
	glUniformMatrix4fv(uniforms["modelID"], 1, GL_FALSE, glm::value_ptr(modelm));
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(view*modelm)));
	glUniformMatrix3fv(uniforms["normalMatrixID"], 1, GL_FALSE, glm::value_ptr(normalMatrix));

/*
	if(isWhite){
		glUniform3f(uniforms["colorID"], 1.0f, 1.0f, 1.0f);
	} else {
		glUniform3f(uniforms["colorID"], 0.0f, 0.0f, 0.0f);
	}
	*/
	Model::Draw(*shaderProgram); 
}

void Piece::place(float xPos, float yPos, float zPos){
	x = xPos;
	y = yPos;
	z = zPos;
	//modelm = glm::translate(modelm, glm::vec3(x, y, z)); // translate it down so it's at the center of the scene
	// 0.6f, -0.9f, 2.85f 
}