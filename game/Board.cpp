#include "Board.hpp"
#include "../environment/Camera.hpp"
#include "../environment/LightSource.hpp"
#include "../modeler/ShaderManager.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include <iostream>
#include <algorithm>

extern environment::Camera* camera;
extern modeler::ShaderManager* shaderManager;
extern environment::LightSource* lightSource;

game::Board::Board(std::string const &path) : Model(path){
	// Board position
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);

	// Tile size
	this->tileSize = glm::vec2(0.50f, 0.50f);

	// Edge size
	this->edge = glm::vec2(0.25f, 0.25f);

	for(int k = 0; k  < 8; k++){
		for (int y = 0; y < 8; y++){
			this->tiles[k][y] = nullptr;
		}
	}

	Piece pawn = Piece("../asset/chessTemp/Pawn.obj", "Pawn", true);
	Piece rook = Piece("../asset/chessTemp/Rook.obj", "Rook", true);
	Piece knight = Piece("../asset/chessTemp/Knight.obj", "Horse", true);
	Piece bishop = Piece("../asset/chessTemp/Bishop.obj", "Bishop", true);
	Piece queen = Piece("../asset/chessTemp/Queen.obj", "Queen", true);
	Piece king = Piece("../asset/chessTemp/King.obj", "King", true);

	for (int i = 0; i < 8; ++i){
		pawn.setTeam(true);
		this->tiles[i][1] = new Piece(pawn);
		pawn.setTeam(false);
		this->tiles[i][6] = new Piece(pawn);	
	}

	tiles[0][0] = new Piece(rook);
	tiles[1][0] = new Piece(knight);
	tiles[2][0] = new Piece(bishop);
	tiles[3][0] = new Piece(queen);
	tiles[4][0] = new Piece(king);
	tiles[5][0] = new Piece(bishop);
	tiles[6][0] = new Piece(knight);
	tiles[7][0] = new Piece(rook);
	
	rook.setTeam(false);
	knight.setTeam(false);
	bishop.setTeam(false);
	queen.setTeam(false);
	king.setTeam(false);

	tiles[0][7] = new Piece(rook);
	tiles[1][7] = new Piece(knight);
	tiles[2][7] = new Piece(bishop);
	tiles[3][7] = new Piece(queen);
	tiles[4][7] = new Piece(king);
	tiles[5][7] = new Piece(bishop);
	tiles[6][7] = new Piece(knight);
	tiles[7][7] = new Piece(rook);
	
	float offset = 1.15f;
	
	float x, y, z;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(tiles[i][j] != nullptr){
				x = this->position.x + (-tileSize.x*4 + edge.x + (tileSize.x * i));
				y = this->position.y;
				z = this->position.y + (-tileSize.y*4 + edge.y + (tileSize.y * j));

				tiles[i][j]->place(glm::vec3(x, y, z));
				tiles[i][j]->setFirstMove(true);
			}
		}
	}

	shaderProgram = shaderManager->getShader(std::vector<std::pair<GLenum, std::string>>{
		{GL_VERTEX_SHADER, "../shader/vertex.vert"},
		{GL_FRAGMENT_SHADER, "../shader/fragment.frag"},
	});

	// Select no-one!
	this->selected = std::pair<int, int>(-1, -1);
};

void game::Board::movePiece(int indexI, int indexJ, int destinationI, int destinationJ){	
	
	std::vector<std::pair<int, int>> allAvailableMoves = moveToIndex(indexI, indexJ);
	glm::vec3 newPosition, position;

	for(auto v : allAvailableMoves){
		if(v.first == destinationI && v.second == destinationJ){
			if(animationTile == nullptr){
				animationTile = new std::pair<std::pair<int, int>,std::pair<int, int>>{
					{indexI, indexJ},
					{destinationI,destinationJ}
				};
			}
			glm::vec3 destination = glm::vec3(
				(this->position.x + (-tileSize.x * 4 + edge.x + (tileSize.x * destinationI))),
				 this->position.y, 
				(this->position.y + (-tileSize.y * 4 + edge.y + (tileSize.y * destinationJ)))
			);

			position = glm::vec3(
				(this->position.x + (-tileSize.x * 4 + edge.x + (tileSize.x * indexI))),
				 this->position.y, 
				(this->position.y + (-tileSize.y * 4 + edge.y + (tileSize.y * indexJ)))
			);

			if(tiles[indexI][indexJ]->getName() == "Horse"){
				
				glm::vec3 midpoint = glm::vec3((position.x + destination.x)/2, 1.0f, (position.z + destination.z)/2);
				
				newPosition = jumpCurve(position, midpoint, destination, std::min(this->animationTime, 1.0f));
				tiles[indexI][indexJ]->place(newPosition);

			} else {

				newPosition = lerp(position, destination, std::min(this->animationTime, 1.0f));
				tiles[indexI][indexJ]->place(newPosition);
			}	
		}
		setSelection(std::pair<int, int>(indexI, indexJ));
	}

	if(this->animationTime >= 1.0f){
		clearSelection();
		tiles[indexI][indexJ]->setFirstMove(false);
		tiles[destinationI][destinationJ] = tiles[indexI][indexJ];
		//delete tiles[indexI][indexJ];
		tiles[indexI][indexJ] = nullptr;
		this->animationTime = 0.0f;
		animationTile = nullptr;
	}
}

auto game::Board::moveToIndex(int indexI, int indexJ) -> std::vector<std::pair<int, int>> {
	std::vector<std::pair<int, int>> allAvailableMoves;
	std::vector<std::string> movesList;

	if(tiles[indexI][indexJ]){
		movesList = tiles[indexI][indexJ]->getMoves();
	
		for(auto move : movesList){
			if(move == "F"){
				int j = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexJ + 1 : indexJ - 1);
				int j2 = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexJ + 2 : indexJ - 2);												
				std::pair<int, int> attackLeft( 
					((tiles[indexI][indexJ]->isWhiteTeam()) ? indexI + 1 : indexI - 1),
					((tiles[indexI][indexJ]->isWhiteTeam()) ? indexJ + 1 : indexJ - 1)
				);
				std::pair<int, int> attackRight( 
					((tiles[indexI][indexJ]->isWhiteTeam()) ? indexI - 1 : indexI + 1),
					((tiles[indexI][indexJ]->isWhiteTeam()) ? indexJ + 1 : indexJ - 1)
				);																				
				// If inside board
				if(insideBoard(indexI, j)){
					// If pawn and if forward tile is empty
					if(tiles[indexI][indexJ]->getName() == "Pawn"){
						if(tiles[indexI][j] == nullptr){ 
							allAvailableMoves.push_back(std::pair<int, int>(indexI, j));
							if(tiles[indexI][j2] == nullptr && tiles[indexI][indexJ]->isFirstMove()){
								allAvailableMoves.push_back(std::pair<int, int>(indexI, j2));							
							}
						}
						if(insideBoard(attackLeft.first, attackLeft.second) && tiles[attackLeft.first][attackLeft.second] != nullptr && 
							diffColor(indexI, indexJ, attackLeft.first, attackLeft.second)){

							allAvailableMoves.push_back(attackLeft);														
						}
						if(insideBoard(attackRight.first, attackRight.second) && tiles[attackRight.first][attackRight.second] != nullptr && 
							diffColor(indexI, indexJ, attackRight.first, attackRight.second)){
								
							allAvailableMoves.push_back(attackRight);														
						}
					} 
					// If king and forwards tile is empty						
					else if(tiles[indexI][j] == nullptr && tiles[indexI][indexJ]->getName() == "King"){
						allAvailableMoves.push_back(std::pair<int, int>(indexI, j));
					}
					// If king and forwards tile is enemy piece 
					else if (diffColor(indexI, indexJ, indexI, j) && tiles[indexI][indexJ]->getName() == "King"){
						allAvailableMoves.push_back(std::pair<int, int>(indexI, j));
					}
				}
			} else if (move == "B"){
				int j = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexJ - 1 : indexJ + 1);
				// If inside board
				if(insideBoard(indexI, j)){
					// If backwards tile is empty						
					if(tiles[indexI][j] == nullptr){
						allAvailableMoves.push_back(std::pair<int, int>(indexI, j));
					}
					// If backwards tile is enemy piece 
					else if (diffColor(indexI, indexJ, indexI, j)){
						allAvailableMoves.push_back(std::pair<int, int>(indexI, j));
					}
				}
			} else if (move == "L"){
				int i = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexI + 1 : indexI - 1);	
				// If inside board
				if(insideBoard(i, indexJ)){
					// If leftwards tile is empty						
					if(tiles[i][indexJ] == nullptr){
						allAvailableMoves.push_back(std::pair<int, int>(i, indexJ));
					}
					// If leftwards tile is enemy piece 
					else if (diffColor(indexI, indexJ, i, indexJ)){
						allAvailableMoves.push_back(std::pair<int, int>(i, indexJ));
					}
				}
			} else if (move == "R"){
				int i = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexI - 1 : indexI + 1);	
				// If inside board
				if(insideBoard(i, indexJ)){
					// If leftwards tile is empty						
					if(tiles[i][indexJ] == nullptr){
						allAvailableMoves.push_back(std::pair<int, int>(i, indexJ));
					}
					// If leftwards tile is enemy piece 
					else if (diffColor(indexI, indexJ, i, indexJ)){
						allAvailableMoves.push_back(std::pair<int, int>(i, indexJ));
					}
				}
			} else if (move == "F*"){
				int j = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexJ + 1 : indexJ - 1);
				for( ; 
					((tiles[indexI][indexJ]->isWhiteTeam()) ? j < 8 : j >= 0); 
					((tiles[indexI][indexJ]->isWhiteTeam()) ? j++ : j--)) {
						
					if(tiles[indexI][j] == nullptr){
						allAvailableMoves.push_back(std::pair<int, int>(indexI, j));
					} else if(diffColor(indexI, indexJ, indexI, j)){
						allAvailableMoves.push_back(std::pair<int, int>(indexI, j));
						break;
					} else if(!diffColor(indexI, indexJ, indexI, j)){
						break;
					}
				}
			}else if (move == "B*"){
				int j = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexJ - 1 : indexJ + 1);	
				for( ; 
					((tiles[indexI][indexJ]->isWhiteTeam()) ? j >= 0 : j < 8); 
					((tiles[indexI][indexJ]->isWhiteTeam()) ? j-- : j++)) {
						
					if(tiles[indexI][j] == nullptr){
						allAvailableMoves.push_back(std::pair<int, int>(indexI, j));
					} else if(diffColor(indexI, indexJ, indexI, j)){
						allAvailableMoves.push_back(std::pair<int, int>(indexI, j));
						break;
					} else if(!diffColor(indexI, indexJ, indexI, j)){
						break;
					}
				}
			} else if (move == "L*") {
				int i = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexI + 1 : indexI - 1);	
				for( ; 
					((tiles[indexI][indexJ]->isWhiteTeam()) ? i < 8 : i >= 0); 
					((tiles[indexI][indexJ]->isWhiteTeam()) ? i++ : i--)) {
						
					if(tiles[i][indexJ] == nullptr){
						allAvailableMoves.push_back(std::pair<int, int>(i, indexJ));
					} else if(diffColor(indexI, indexJ, i, indexJ)){
						allAvailableMoves.push_back(std::pair<int, int>(i, indexJ));
						break;
					} else if(!diffColor(indexI, indexJ, i, indexJ)){
						break;
					}
				}
			} else if (move == "R*"){
				int i = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexI - 1 : indexI + 1);	
				for( ; 
					((tiles[indexI][indexJ]->isWhiteTeam()) ? i >= 0 : i < 8); 
					((tiles[indexI][indexJ]->isWhiteTeam()) ? i-- : i++)) {
						
					if(tiles[i][indexJ] == nullptr){
						allAvailableMoves.push_back(std::pair<int, int>(i, indexJ));
					} else if(diffColor(indexI, indexJ, i, indexJ)){
						allAvailableMoves.push_back(std::pair<int, int>(i, indexJ));
						break;
					} else if(!diffColor(indexI, indexJ, i, indexJ)){
						break;
					}
				}
			} else if (move == "(FR)*"){
				int i = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexI - 1 : indexI + 1);
				int j = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexJ + 1 : indexJ - 1);	
				for( ; 
					insideBoard(i, j); 
					((tiles[indexI][indexJ]->isWhiteTeam()) ? i-- : i++), 
						((tiles[indexI][indexJ]->isWhiteTeam()) ? j++ : j--)){
					
					if(tiles[i][j] == nullptr){
						allAvailableMoves.push_back(std::pair<int, int>(i, j));
					} else if(diffColor(indexI, indexJ, i, j)){
						allAvailableMoves.push_back(std::pair<int, int>(i, j));
						break;
					} else if(!diffColor(indexI, indexJ, i, j)){
						break;
					}
				}
			} else if (move == "(FL)*"){
				int i = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexI + 1 : indexI - 1);
				int j = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexJ + 1 : indexJ - 1);	
				for( ; 
					insideBoard(i, j); 
					((tiles[indexI][indexJ]->isWhiteTeam()) ? i++ : i--), 
						((tiles[indexI][indexJ]->isWhiteTeam()) ? j++ : j--)){
					
					if(tiles[i][j] == nullptr){
						allAvailableMoves.push_back(std::pair<int, int>(i, j));
					} else if(diffColor(indexI, indexJ, i, j)){
						allAvailableMoves.push_back(std::pair<int, int>(i, j));
						break;
					} else if(!diffColor(indexI, indexJ, i, j)){
						break;
					}
				}
			} else if (move == "(BR)*"){
				int i = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexI - 1 : indexI + 1);
				int j = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexJ - 1 : indexJ + 1);	
				for( ; 
					insideBoard(i, j); 
					((tiles[indexI][indexJ]->isWhiteTeam()) ? i-- : i++), 
						((tiles[indexI][indexJ]->isWhiteTeam()) ? j-- : j++)){
					
					if(tiles[i][j] == nullptr){
						allAvailableMoves.push_back(std::pair<int, int>(i, j));
					} else if(diffColor(indexI, indexJ, i, j)){
						allAvailableMoves.push_back(std::pair<int, int>(i, j));
						break;
					} else if(!diffColor(indexI, indexJ, i, j)){
						break;
					}
				}
			} else if (move == "(BL)*"){
				int i = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexI + 1 : indexI - 1);
				int j = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexJ - 1 : indexJ + 1);	
				for( ; 
					insideBoard(i, j); 
					((tiles[indexI][indexJ]->isWhiteTeam()) ? i++ : i--), 
						((tiles[indexI][indexJ]->isWhiteTeam()) ? j-- : j++)){
					
					if(tiles[i][j] == nullptr){
						allAvailableMoves.push_back(std::pair<int, int>(i, j));
					} else if(diffColor(indexI, indexJ, i, j)){
						allAvailableMoves.push_back(std::pair<int, int>(i, j));
						break;
					} else if(!diffColor(indexI, indexJ, i, j)){
						break;
					}
				}
			} else if (move == "FFR"){
				int i = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexI - 1 : indexI + 1);
				int j = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexJ + 2 : indexJ - 2);					

				if (insideBoard(i, j) && tiles[i][j] == nullptr) {
					allAvailableMoves.push_back(std::pair<int, int>(i, j));
				} else if (insideBoard(i, j) && diffColor(indexI, indexJ, i, j)){
					allAvailableMoves.push_back(std::pair<int, int>(i, j));						
				}
			} else if (move == "FFL"){
				int i = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexI + 1 : indexI - 1);
				int j = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexJ + 2 : indexJ - 2);					

				if (insideBoard(i, j) && tiles[i][j] == nullptr) {
					allAvailableMoves.push_back(std::pair<int, int>(i, j));
				} else if (insideBoard(i, j) && diffColor(indexI, indexJ, i, j)){
					allAvailableMoves.push_back(std::pair<int, int>(i, j));						
				}
			} else if (move == "BBR"){
				int i = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexI - 1 : indexI + 1);
				int j = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexJ - 2 : indexJ + 2);					

				if (insideBoard(i, j) && tiles[i][j] == nullptr) {
					allAvailableMoves.push_back(std::pair<int, int>(i, j));
				} else if (insideBoard(i, j) && diffColor(indexI, indexJ, i, j)){
					allAvailableMoves.push_back(std::pair<int, int>(i, j));						
				}
			} else if (move == "BBL"){
				int i = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexI + 1 : indexI - 1);
				int j = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexJ - 2 : indexJ + 2);					

				if (insideBoard(i, j) && tiles[i][j] == nullptr) {
					allAvailableMoves.push_back(std::pair<int, int>(i, j));
				} else if (insideBoard(i, j) && diffColor(indexI, indexJ, i, j)){
					allAvailableMoves.push_back(std::pair<int, int>(i, j));						
				}
			} else if (move == "LLF"){
				int i = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexI + 2 : indexI - 2);
				int j = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexJ + 1 : indexJ - 1);					

				if (insideBoard(i, j) && tiles[i][j] == nullptr) {
					allAvailableMoves.push_back(std::pair<int, int>(i, j));
				} else if (insideBoard(i, j) && diffColor(indexI, indexJ, i, j)){
					allAvailableMoves.push_back(std::pair<int, int>(i, j));						
				}
			} else if (move == "LLB"){
				int i = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexI + 2 : indexI - 2);
				int j = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexJ - 1 : indexJ + 1);					

				if (insideBoard(i, j) && tiles[i][j] == nullptr) {
					allAvailableMoves.push_back(std::pair<int, int>(i, j));
				} else if (insideBoard(i, j) && diffColor(indexI, indexJ, i, j)){
					allAvailableMoves.push_back(std::pair<int, int>(i, j));						
				}
			} else if (move == "RRF"){
				int i = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexI - 2 : indexI + 2);
				int j = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexJ + 1 : indexJ - 1);					

				if (insideBoard(i, j) && tiles[i][j] == nullptr) {
					allAvailableMoves.push_back(std::pair<int, int>(i, j));
				} else if (insideBoard(i, j) && diffColor(indexI, indexJ, i, j)){
					allAvailableMoves.push_back(std::pair<int, int>(i, j));						
				}
			} else if (move == "RRB"){
				int i = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexI - 2 : indexI + 2);
				int j = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexJ - 1 : indexJ + 1);					

				if (insideBoard(i, j) && tiles[i][j] == nullptr) {
					allAvailableMoves.push_back(std::pair<int, int>(i, j));
				} else if (insideBoard(i, j) && diffColor(indexI, indexJ, i, j)){
					allAvailableMoves.push_back(std::pair<int, int>(i, j));						
				}
			} else if (move == "(FR)"){
				int i = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexI - 1 : indexI + 1);
				int j = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexJ + 1 : indexJ - 1);					

				if (insideBoard(i, j) && tiles[i][j] == nullptr) {
					allAvailableMoves.push_back(std::pair<int, int>(i, j));
				} else if (insideBoard(i, j) && diffColor(indexI, indexJ, i, j)){
					allAvailableMoves.push_back(std::pair<int, int>(i, j));						
				}
			} else if (move == "(FL)"){
				int i = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexI + 1 : indexI - 1);
				int j = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexJ + 1 : indexJ - 1);					

				if (insideBoard(i, j) && tiles[i][j] == nullptr) {
					allAvailableMoves.push_back(std::pair<int, int>(i, j));
				} else if (insideBoard(i, j) && diffColor(indexI, indexJ, i, j)){
					allAvailableMoves.push_back(std::pair<int, int>(i, j));						
				}
			} else if (move == "(BL)"){
				int i = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexI + 1 : indexI - 1);
				int j = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexJ - 1 : indexJ + 1);					

				if (insideBoard(i, j) && tiles[i][j] == nullptr) {
					allAvailableMoves.push_back(std::pair<int, int>(i, j));
				} else if (insideBoard(i, j) && diffColor(indexI, indexJ, i, j)){
					allAvailableMoves.push_back(std::pair<int, int>(i, j));						
				}
			} else if (move == "(BR)"){
				int i = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexI - 1 : indexI + 1);
				int j = ((tiles[indexI][indexJ]->isWhiteTeam()) ? indexJ - 1 : indexJ + 1);					

				if (insideBoard(i, j) && tiles[i][j] == nullptr) {
					allAvailableMoves.push_back(std::pair<int, int>(i, j));
				} else if (insideBoard(i, j) && diffColor(indexI, indexJ, i, j)){
					allAvailableMoves.push_back(std::pair<int, int>(i, j));						
				}
			}
		}	
	}
	return allAvailableMoves;
}

void game::Board::update(float dt){

	if(animationTile != nullptr){
		this->animationTime += dt;
		movePiece(animationTile->first.first, animationTile->first.second, animationTile->second.first, animationTile->second.second);
	}

	// Update all pieces
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(this->tiles[i][j] != nullptr){
				this->tiles[i][j]->update(dt);
			}
		}
	}

	this->draw();
}

void game::Board::draw(){

	this->shaderProgram->bind();

	glm::mat4 view = camera->getViewMatrix(); 
	
	glm::mat4 projection = camera->getPerspectiveMatrix();

	glm::vec3 lightPosition = lightSource->getPosition();
	glm::vec3 attenuation = lightSource->getAttenuation(); 
	glm::vec3 lightColor = lightSource->getColor();

	std::map<std::string, GLuint> uniforms = shaderProgram->getUniform(	std::map<std::string, GLchar*>({
		{"viewID", "view"},
		{"projectionID", "projection"},
		{"modelID", "model"},
		{"normalMatrixID", "normalMatrix"},
		{"lightSourcePositionID","lightSourcePosition"},
		{"camPosID", "CamPos"},
		{"attenuationAID", "attenuationA"},
		{"attenuationBID", "attenuationB"},
		{"attenuationCID", "attenuationC"},
		{"lightColorID", "lightColor"}
	}));

	glUniform1f(uniforms["attenuationAID"], attenuation.x);
	glUniform1f(uniforms["attenuationBID"], attenuation.y);
	glUniform1f(uniforms["attenuationCID"], attenuation.z);
	glUniform3fv(uniforms["lightColorID"], 1, value_ptr(lightColor));
	glUniform3fv(uniforms["lightSourcePositionID"], 1, value_ptr(lightPosition));

	glUniform3fv(uniforms["camPosID"], 1, value_ptr(camera->getPos()));												//glm::mat4 model = glm::rotate(glm::mat4(), time, glm::vec3(0, 1, 0));

	glUniformMatrix4fv(uniforms["viewID"], 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(uniforms["projectionID"], 1, GL_FALSE, glm::value_ptr(projection));

	glm::mat4 modelm;

	modelm = glm::translate(modelm, this->position); // Translate it down so it's at the center of the scene.
	modelm = glm::scale(modelm, glm::vec3(0.4f, 0.4f, 0.4f));	

	glUniformMatrix4fv(uniforms["modelID"], 1, GL_FALSE, glm::value_ptr(modelm));
	
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(view*modelm)));

	glUniformMatrix3fv(uniforms["normalMatrixID"], 1, GL_FALSE, glm::value_ptr(normalMatrix));
	
	Model::Draw(*shaderProgram); 

	shaderProgram->unbind();

	// Draw each piece. 
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(this->tiles[i][j] != nullptr){
				this->tiles[i][j]->draw();
			}
		}
	}
}

auto game::Board::lerp(glm::vec3 a, glm::vec3 b, float dt) -> glm::vec3 {
	glm::vec3 point;

	point.x = a.x * (1 - dt) + b.x * dt;
	point.y = a.y * (1 - dt) + b.y * dt;
	point.z = a.z * (1 - dt) + b.z * dt;

	return point;
}

auto game::Board::getPoint(float p0, float p1, float dt) -> float{
	float diff = p1 - p0;

	return p0 + (diff * dt);
}

auto game::Board::jumpCurve(glm::vec3 a, glm::vec3 b, glm::vec3 c, float dt) -> glm::vec3{
	glm::vec3 point1, point2, result;

	point1 = glm::vec3(
		getPoint(a.x, b.x, dt), 
		getPoint(a.y, b.y, dt), 
		getPoint(a.z, b.z, dt)
	);

	point2 = glm::vec3(
		getPoint(b.x, c.x, dt), 
		getPoint(b.y, c.y, dt), 
		getPoint(b.z, c.z, dt)
	);

	result = glm::vec3(
		getPoint(point1.x, point2.x, dt), 
		getPoint(point1.y, point2.y, dt), 
		getPoint(point1.z, point2.z, dt)
	);

  	return result;
}

glm::vec2 game::Board::getTileSize()
{
	return this->tileSize;
}

glm::vec3 game::Board::getPosition()
{
	return this->position;
}

std::pair<int, int> game::Board::getSelected()
{
	return this->selected;
}

bool game::Board::hasSelection()
{	
	return (this->selected.first != -1 && this->selected.second != -1);
}

bool game::Board::hasPieceAt(int x, int y)
{
	return (this->tiles[x][y] != nullptr);
}

int game::Board::pieceColorAt(int x, int y)
{	
	if (!this->hasPieceAt(x, y))
	{
		return -1;
	}

	return (this->tiles[x][y]->isWhiteTeam()) ? 1 : 0;
}

void game::Board::setSelection(std::pair<int, int> selection)
{
	this->selected = selection;
	
	if(tiles[this->selected.first][this->selected.second] != nullptr)
		tiles[this->selected.first][this->selected.second]->setSelected(true);
}

void game::Board::clearSelection()
{	
	if(tiles[this->selected.first][this->selected.second] != nullptr)
		this->tiles[this->selected.first][this->selected.second]->setSelected(false);
	
	this->selected = std::pair<int, int>(-1, -1);
}

bool game::Board::insideBoard(int i, int j){
	return ((i >= 0 && i < 8) && (j >= 0 && j < 8));
}

bool game::Board::diffColor(int currentI, int currentJ, int targetI, int targetJ){
	return tiles[currentI][currentJ]->isWhiteTeam() != tiles[targetI][targetJ]->isWhiteTeam();
}