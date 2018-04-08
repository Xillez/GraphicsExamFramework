#include "../header/piece.hpp"
#include "../header/globalVar.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>




Piece::Piece(std::string const &path, std::string const &pieceName) : Model(path){
	std::unordered_map<std::string, std::vector<std::string>>::iterator found = moves.find(pieceName);

	if(found == moves.end()){
		std::cout << "There are no moves for a piece called " << pieceName << '\n';
	}
	else {
		/*for(auto v : found->second){
			move.push_back(v);
		}*/
		move = found->second;
	}

	shaderProgram = new Shader("../shader/vertexPiece.vert", "../shader/fragmentPiece.frag");
	shaderProgram->bind();
}


void Piece::drawPiece(){
		static float time = 0.0;
	time += .01;
	//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 projection = glm::perspective(3.14f / 3.0f, (GLfloat)1024 / (GLfloat)768, 0.1f, -10.0f);
	GLint viewID = glGetUniformLocation(shaderProgram->id(), "view");
	GLint projectionID = glGetUniformLocation(shaderProgram->id(), "projection");
	GLint modelID = glGetUniformLocation(shaderProgram->id(), "model");
	GLint normalMatrixID = glGetUniformLocation(shaderProgram->id(), "normalMatrix");
	glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(projection));
	glm::mat4 modelm;
	modelm = glm::translate(modelm, glm::vec3(0.0f, -1.75f, -1.0f)); // translate it down so it's at the center of the scene
	modelm = glm::scale(modelm, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
															//glm::mat4 model = glm::rotate(glm::mat4(), time, glm::vec3(0, 1, 0));
	//model = glm::rotate(model, time, glm::vec3(0, 1, 0));														//ourShader.setMat4("model", model);
	glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(modelm));
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(view*modelm)));
	glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, glm::value_ptr(normalMatrix));
	
	Model::Draw(*shaderProgram); 
	 //printf("hello\t");
}