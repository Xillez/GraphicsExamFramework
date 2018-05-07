#pragma once

#include <string>
#include <vector>
#include <functional>

/**
 * @brief Container for functions used across application.
 */
namespace helpers{

	/**
	 * @brief Gets destination set based on moveset specified as strings.
	 * 
	 * @param moveList - List of strings representing each possible movement. 
	 * @return Destination tile set relative to current tile and validaors for each move.
	 */
std::vector<								// All resulting moves
	std::pair<
		std::pair<int, int>,				// Destination of parsed move.
		std::vector<std::function<bool()>>	// Validators to check if move is legal.
	>
>  parseMoveList(std::vector<std::string> moveList);

	/**
	 * @brief Gets destination based on move specified as string
	 * @details Recursivly goes through string until destination is determined.
	 * 
	 * @param move specified as a string with a regex like syntax.
	 *  
	 * @return destination of the move relative to current tile with validator functions.
	 */
	std::pair<
		std::pair<int, int>,				// Destination of parsed move.
		std::vector<std::function<bool()>>	// Validators to check if move is legal.
	> parseMove(std::string move);

	/**
	 * @brief Creates a validator based on given action
	 * 
	 * @return Effect on affected piece with posible move and behavior.
	 */
	std::pair<
		std::pair<int, int>,				// Destination affected piece might move to.
		std::vector<std::function<bool()>>	// Functional effect on piece.
	> parseAction(std::string move);

	/**
	 * @brief Parses an attack that affect a piece
	 * 
	 * @return returns a pair with empty move for affected piece and effect on piece
	 */
	std::pair<
		std::pair<int, int>,				// Destination affected piece might move to.
		std::vector<std::function<bool()>>	// Functional effect on piece.
	> parseAttack(std::string move);

	/**
	 * @brief Parses a replacement that affect a piece.
	 * 
	 * @return returns a pair with empty move for affected piece and effect on piece
	 */
	std::pair<
		std::pair<int, int>,				// Destination affected piece might move to.
		std::vector<std::function<bool()>>	// Functional effect on piece.
	> parseReplace(std::string move);
}