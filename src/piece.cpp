#include "../header/piece.hpp"
#include <iostream>




Piece::Piece(std::string const &path, std::string const &pieceName){
	std::unordered_map<std::string, std::vector<std::string>>::iterator found = moves.find(pieceName);

	if(found == moves.end()){
		std::cout << "There are no moves for a piece called " << pieceName << '\n';
	}
	else {
		for(auto v : found->second){
			move.push_back(v);
		}
	}
}


void Piece::draw(){

}