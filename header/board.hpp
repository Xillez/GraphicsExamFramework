#pragma once
#include "piece.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <string>

/**
 * @brief 8x8 board represents pieces on each tile 
 * @details [long description]
 * 
 */
class Board : Model{
public:
	/**
	 * @brief Board constructor
	 */
	Board(std::string const &path);
	/**
	 * @brief move piece to the desired destination on the board
	 * @details [long description]
	 * 
	 * @param indexI first index of the tiles/piece on the board
	 * @param indexJ second index of the tiles/piece on the board
	 * @param destinationI first index of tiles on the board
	 * @param destinationJ second index of tiles on the board
	 */
	void movePiece(int indexI, int indexJ, float destinationI, float destinationJ);
	
	/**
	 * @brief draw the board and every piece found
	 */
	void draw();

	glm::vec2 getTileSize();
	glm::vec3 getPosition();
	glm::vec2 getEdge();
private:

	Piece* tiles[8][8];
	glm::vec2 tileSize;							//!< tile size
	glm::vec3 pos;								//!< center of board

	Shader* shaderProgram;

	float attenuationA = 1.0f;
	float attenuationB = 0.2f;
	float attenuationC = 0.0f;

	glm::vec3 lightSourcePosition = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec2 edge;								//!< board edges

};