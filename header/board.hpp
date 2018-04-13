#pragma once
#include "piece.hpp"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.hpp"
#include <string>

/**
 * @brief 8x8 board represents pieces on each tile 
 */
class Board : Model{
public:
	
	/**
	 * @brief Board constructor
	 */
	Board(std::string const &path);
	
	/**
	 * @brief move piece to the desired destination on the board
	 *
	 * @param indexI first index of the tiles/piece on the board
	 * @param indexJ second index of the tiles/piece on the board
	 * @param destinationI first index of tiles on the board
	 * @param destinationJ second index of tiles on the board
	 */
	void movePiece(int indexI, int indexJ, int destinationI, int destinationJ);
	
	/**
	 * @brief draw the board and every piece found
	 */
	void draw();

	/**
	 * @brief Convert piece moves to indecies for tiles[][]
	 * 
	 * @param indexI is the x location of the piece
	 * @param indexJ is the y location of the piece
	 * 
	 * @return returns a vector of new indecies that a piece can move to
	 */
	auto moveToIndex(int indexI, int indexJ) -> std::vector<std::pair<int, int>>;

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