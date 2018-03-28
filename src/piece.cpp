#include "../header/piece.hpp"
#include "../header/globalVar.hpp"
#include <iostream>


Piece::Piece(std::string const &path, std::string const &pieceName) : Model(path){

	std::unordered_map<std::string, std::vector<std::string>>::iterator found = moves.find(pieceName);

	if(found == moves.end()){
		std::cout << "There are no moves for a piece called " << pieceName << '\n';
	}
	else {
		for(auto v : found->second){
			move.push_back(v);
		}
	}
	x = y = 0;
}


void Piece::draw(){

}
