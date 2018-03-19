#include "gl_model.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


class Piece : Model {
private:
	std::vector<std::string> move;
	int x, y;

public:
	Piece() {};
	Piece(std::string const &path, std::string const &pieceName){
		std::string name;
	
	};
	void draw() {};
};