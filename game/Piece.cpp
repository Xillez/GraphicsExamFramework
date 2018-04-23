#include "Piece.hpp"
#include "../header/globalVar.hpp"
#include "../environment/Camera.hpp"
#include "../environment/LightSource.hpp"

#include "../modeler/ShaderManager.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

extern environment::Camera* camera;
extern std::unordered_map<std::string, std::vector<std::string>> moves;
extern modeler::ShaderManager* shaderManager;
extern environment::LightSource* lightSource;

game::Piece::Piece(std::string const &path, std::string const &pieceName, bool isWhite) : Model(path){

	std::unordered_map<std::string, std::vector<std::string>>::iterator found = moves.find(pieceName);

	if(found == moves.end()){
		printf("%s There are no moves for a piece called %s\n", TAG_WARN.c_str(),pieceName );
	}
	else {
		this->move = found->second;
	}
	this->selected = false;
	this->isWhite = isWhite;
	this->name = pieceName;
	this->firstMove = true;

	this->shaderProgram = shaderManager->getShader(std::vector<std::pair<GLenum, std::string>>{
		{GL_VERTEX_SHADER, "../shader/vertex.vert"},
		{GL_FRAGMENT_SHADER, "../shader/fragmentPiece.frag"},
	});
}

void game::Piece::update(float dt){
	// NOTE: added for sake of structure, remove comment if piece need update function.
}

void game::Piece::draw(){
	this->shaderProgram->bind();

	glm::mat4 view = camera->getViewMatrix(); 
	
	glm::mat4 projection = camera->getPerspectiveMatrix();

	glm::vec3 lightPosition = lightSource->getPosition();
	glm::vec3 attenuation = lightSource->getAttenuation(); 
	glm::vec3 lightColor = lightSource->getColor();

	std::map<std::string, GLuint> uniforms = shaderProgram->getUniform(	std::map<std::string, std::string>({
		{"viewID", "view"},
		{"projectionID", "projection"},
		{"modelID", "model"},
		{"normalMatrixID", "normalMatrix"},
		{"lightSourcePositionID","lightSourcePosition"},
		{"camPosID", "CamPos"},
		{"attenuationAID", "attenuationA"},
		{"attenuationBID", "attenuationB"},
		{"attenuationCID", "attenuationC"},
		{"lightColorID", "lightColor"},
		{"colorID", "color"}
	}));

	glUniform1f(uniforms["attenuationAID"], attenuation.x);
	glUniform1f(uniforms["attenuationBID"], attenuation.y);
	glUniform1f(uniforms["attenuationCID"], attenuation.z);
	glUniform3fv(uniforms["lightColorID"], 1, value_ptr(lightColor));
	glUniform3fv(uniforms["lightSourcePositionID"], 1, value_ptr(lightPosition));

	glUniform3fv(uniforms["camPosID"], 1, value_ptr(camera->getPos()));	

	glUniformMatrix4fv(uniforms["viewID"], 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(uniforms["projectionID"], 1, GL_FALSE, glm::value_ptr(projection));
	
	glm::mat4 modelm;

	modelm = glm::translate(modelm, this->pos); 
	modelm = glm::scale(modelm, glm::vec3(0.02f, 0.02f, 0.02f)); //glm::vec3(0.015f, 0.015f, 0.015f));
															
	glUniformMatrix4fv(uniforms["modelID"], 1, GL_FALSE, glm::value_ptr(modelm));

	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(view*modelm)));

	glUniformMatrix3fv(uniforms["normalMatrixID"], 1, GL_FALSE, glm::value_ptr(normalMatrix));


	if(selected){
		glm::vec3 color(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniforms["colorID"], 1, glm::value_ptr(color));
	} else {
		glm::vec3 color(((isWhite) ? (1.0f, 1.0f, 1.0f) : (0.7f, 0.7f, 0.7f)));
		glUniform3fv(uniforms["colorID"], 1, glm::value_ptr(color));	
	}
	

	Model::Draw(*shaderProgram); 

	this->shaderProgram->unbind();
}

void game::Piece::place(glm::vec3 position){
	this->pos = position;
}

auto game::Piece::getMoves() -> std::vector<std::string>{
	return move;
}

auto game::Piece::getName() -> std::string {
	return name;
}

auto game::Piece::getPosition() -> glm::vec3 {
	return pos;
}

bool game::Piece::isFirstMove(){
	return firstMove;
}

bool game::Piece::isWhiteTeam(){
	return isWhite;
}

void game::Piece::setTeam(bool team){
	isWhite = team;
}

void game::Piece::setSelected(bool select){
	this->selected = select;
}

void game::Piece::setFirstMove(bool fm){
	this->firstMove = fm;
}