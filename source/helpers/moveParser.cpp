#include "moveParser.hpp"
#include "../header/globalVar.hpp"
#include <stdio.h>
#include <utility>


std::vector<								// All resulting moves
	std::pair<
		std::pair<int, int>,				// Destination of parsed move.
		std::vector<std::function<bool()>>	// Validators to check if move is legal.
	>
> helpers::parseMoveList(std::vector<std::string> moveList){
	
	std::vector<								// All resulting moves
		std::pair<
			std::pair<int, int>,				// Destination of parsed move.
			std::vector<std::function<bool()>>	// Validators to check if move is legal.
		>
	> alteredMoveList;				// Variable to return


	for(std::string it : moveList){
		printf("%s Parsing move: %s \n", TAG_DEBUG.c_str(), it.c_str());
		alteredMoveList.push_back(parseMove(it));
	}
	return alteredMoveList;
}

std::pair<
	std::pair<int, int>,				// Destination of parsed move.
	std::vector<std::function<bool()>>	// Validators to check if move is legal.
> helpers::parseMove(std::string move)
{
	std::pair<
		std::pair<int, int>,				// Destination of parsed move.
		std::vector<std::function<bool()>>	// Validators to check if move is legal.
	> availableMoves;				// Variable to return

	while(move.length() != 0)
	{
		char current = move.at(0);		// get the next character.
		move.erase(0,1);				// remove character from list.
		switch(current){
			case '(':		//Start parsing group
				{
					auto innerQuery = parseMove(move);	// Get result of inner move.

					availableMoves.first.first += innerQuery.first.first;		// add move result to currenty parsing.		
					availableMoves.first.second += innerQuery.first.second;		// add move result to currenty parsing.

					availableMoves.second.insert(								// Appending validators to current parsing.
						std::end(availableMoves.second), std::begin(innerQuery.second), std::end(innerQuery.second)
					);
					break;
				}
			case ')':		//End parsing group
				return availableMoves;
				break;

			case 'F':		//Move forward
				availableMoves.first.second++;
				break;

			case 'R':		//Move right
				availableMoves.first.first++;
				break;

			case 'B':		//Move back
				availableMoves.first.second--;
				break;

			case 'L':		//Move left
				availableMoves.first.first--;
				break;

			case '$':		//Start action
				parseAction(move);
				break;

			default:
				printf("%s unexpected value: %c\n", TAG_WARN.c_str(), current);
				return availableMoves;
				break;

		}
	}
}

std::pair<
	std::pair<int, int>,				// Destination of parsed move.
	std::vector<std::function<bool()>>	// Validators to check if move is legal.
> helpers::parseAction(std::string move){

	char current = move.at(0);		// get the next character.
	move.erase(0,1);				// remove character from list.
	switch(current){	
		case 'X':
			return parseAttack(move);
			break;
		case 'M':
			return parseMove(move);
			break;
		case 'R':
			return parseReplace(move);
			break;
		default:
			printf("%s unexpected value: %c\n", TAG_WARN.c_str(), current);
			exit(-1);
			break;
	}
}

std::pair<
	std::pair<int, int>,				// Destination of parsed move.
	std::vector<std::function<bool()>>	// Validators to check if move is legal.
> helpers::parseAttack(std::string move){

};

std::pair<
	std::pair<int, int>,				// Destination of parsed move.
	std::vector<std::function<bool()>>	// Validators to check if move is legal.
> helpers::parseReplace(std::string move){

};