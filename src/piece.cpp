#include "../header/piece.hpp"
#include "../header/globalVar.hpp"
#include "../header/camera.hpp"
#include "../class/ShaderManager.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

extern Camera* camera;
extern std::unordered_map<std::string, std::vector<std::string>> moves;


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
	this->selected = false;
	this->isWhite = isWhite;
	this->name = pieceName;
	this->firstMove = true;

	extern ShaderManager* shaderManager;
	this->shaderProgram = shaderManager->getShader(std::vector<std::pair<GLenum, std::string>>{
		{GL_VERTEX_SHADER, "../shader/vertexPiece.vert"},
		{GL_FRAGMENT_SHADER, "../shader/fragmentPiece.frag"},
	});
}


void Piece::draw(){
	this->shaderProgram->bind();

	static float time = 0.0;
	time += .01;
	//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera->getViewMatrix();//glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 projection = camera->getPerspectiveMatrix();//glm::perspective(3.14f / 3.0f, (GLfloat)1024 / (GLfloat)768, 0.1f, -10.0f);
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

	modelm = glm::translate(modelm, pos); // translate it down so it's at the center of the scene
	modelm = glm::scale(modelm, glm::vec3(0.015f, 0.015f, 0.015f));	// it's a bit too big for our scene, so scale it down
															//glm::mat4 model = glm::rotate(glm::mat4(), time, glm::vec3(0, 1, 0));
	//modelm = glm::rotate(modelm, time, glm::vec3(0, 1, 0));														//ourShader.setMat4("model", model);
	glUniformMatrix4fv(uniforms["modelID"], 1, GL_FALSE, glm::value_ptr(modelm));
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(view*modelm)));
	glUniformMatrix3fv(uniforms["normalMatrixID"], 1, GL_FALSE, glm::value_ptr(normalMatrix));


	//std::cout << sizeof(glm::vec3) << '\n';
	if(selected){
		glm::vec3 color(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniforms["colorID"], 1, glm::value_ptr(color));
	} else {
		glm::vec3 color(((isWhite) ? (1.0f, 1.0f, 1.0f) : (0.4f, 0.4f, 0.4f)));
		glUniform3fv(uniforms["colorID"], 1, glm::value_ptr(color));	
	}
	

	Model::Draw(*shaderProgram); 
	this->shaderProgram->unbind();
}

void Piece::place(glm::vec3 position){
	this->pos = position;
	this->firstMove = false;
	//modelm = glm::translate(modelm, glm::vec3(x, y, z)); // translate it down so it's at the center of the scene
	// 0.6f, -0.9f, 2.85f 
}

auto Piece::getMoves() -> std::vector<std::string>{
	return move;
}

auto Piece::getName() -> std::string {
	return name;
}

auto Piece::getPosition() -> glm::vec3 {
	return pos;
}

bool Piece::isFirstMove(){
	return firstMove;
}

bool Piece::pieceColor(){
	return isWhite;
}

void Piece::setColor(bool color){
	isWhite = color;
}

void Piece::setSelected(bool select){
	this->selected = select;
}

void Piece::setFirstMove(bool fm){
	this->firstMove = fm;
}