#pragma once

#include <string>
#include <vector>

/**
 * @brief Container for functions used across application.
 */
namespace helpers{

	/**
	 * @brief Gets destination set based on moveset specified as strings.
	 * 
	 * @param moveList - List of strings representing each possible movement. 
	 * @return Destination tile set relative to current tile.
	 */
	std::vector<std::pair<int, int>> parseMoveList(std::vector<std::string> moveList);
	
	/**
	 * @brief Gets destination based on move specified as string
	 * @details Recursivly goes through string until destination is determined.
	 * 
	 * @param move specified as a string with a regex like syntax.
	 * @return destination of the move relative to current tile.
	 */
	std::pair<int, int> parseMove(std::string move);
}