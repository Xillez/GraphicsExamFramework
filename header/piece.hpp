#pragma once
#include "../class/model.hpp"
#include <glm/glm.hpp>

#include <vector>
#include <string>

/**
 * @brief Piece class represent a individual piece in the board
 * 
 */
class Piece : Model {
private:
	std::vector<std::string> move;
	int x, y;
	Shader* shaderProgram;

public:
	/**
	 * @brief Construct a new Piece object
	 * 
	 */
	Piece();
	
	/**
	 * @brief Construct a new Piece object
	 * 
	 * @param path is .obj file 
	 * @param pieceName is the name of the piece
	 */
	Piece(std::string const &path, std::string const &pieceName);

	/**
	 * @brief 
	 * 
	 */
	void drawPiece();
};