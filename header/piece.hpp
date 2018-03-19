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
	Piece(std::string const &path, std::string const &movePattern, std::string const &pieceName){
		std::ifstream inputFile(movePattern);
		std::string name;
		if (inputFile.is_open()) {
			std::getline(inputFile, name);
			if (name == pieceName) {


			}
		}
	};
	void draw() {};
};