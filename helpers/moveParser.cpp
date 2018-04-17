#include "moveParser.hpp"
#include "../header/globalVar.hpp"
#include <stdio.h>
#include <utility>

std::vector<std::pair<int, int>> helpers::parseMoveList(std::vector<std::string> moveList){
	
	std::vector<std::pair<int,int>> alteredMoveList;


	for(std::string it : moveList){
		printf("%s Parsing move: %s \n", TAG_DEBUG.c_str(), it.c_str());
		alteredMoveList.push_back(parseMove(it));
	}
	return alteredMoveList;
}

std::pair<int, int> helpers::parseMove(std::string move)
{
	std::pair<int, int> availableMoves;

	while(move.length() != 0)
	{
		char current = move.at(0);		// get the next character.
		move.erase(0,1);				// remove character from list.
		switch(current){
			case '(':		//Start parsing group
				{
					std::pair<int, int> innerQuery = parseMove(move);	// Get result of inner move.
					availableMoves.first += innerQuery.first;			// add result to currenty parsing		
					availableMoves.second += innerQuery.second;			// add result to currenty parsing
					break;
				}
			case ')':		//End parsing group
				return availableMoves;
				break;

			case 'F':		//Move forward
				availableMoves.second++;
				break;

			case 'R':		//Move right
				availableMoves.first++;
				break;

			case 'B':		//Move back
				availableMoves.second--;
				break;

			case 'L':		//Move left
				availableMoves.first--;
				break;

			case '$':		//Start action
				//availableMoves.first++;
				break;

			default:
				printf("%s unexpected value: %c\n", TAG_WARN.c_str(), current);
				return availableMoves;
				break;

		}
	}
}