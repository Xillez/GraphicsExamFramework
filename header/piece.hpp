#include "gl_model.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "globalVar.hpp"

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
	Piece() {};
	
	/**
	 * @brief Construct a new Piece object
	 * 
	 * @param path is .obj file 
	 * @param pieceName is the name of the piece
	 */
	Piece(std::string const &path, std::string const &pieceName){
		std::unordered_map<std::string, std::vector<std::string>>::iterator found = moves.find(pieceName);

		if(found == moves.end()){
			std::cout << "There are no moves for a piece called " << pieceName << '\n';
		}
		else {
			for(auto v : found->second){
				move.push_back(v);
			}
		}
	};

	/**
	 * @brief 
	 * 
	 */
	void draw() {};
};