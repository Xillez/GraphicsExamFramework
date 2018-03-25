#pragma once
#include "gl_model.hpp"
#include "globalVar.hpp"  	//!< NOTE: Cause multiple definition problems with global_function.cpp file

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
	void draw();
};