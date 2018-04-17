#pragma once
#include "../modeler/Model.hpp"
#include <glm/glm.hpp>

#include <vector>
#include <string>

/**
 * @brief Container for content specific to chess game.
 */
namespace game{
	/**
	 * @brief Piece class represent a individual piece on the board.
	 */
	class Piece : modeler::Model {
	
	public:
		/**
		 * @brief Construct a new Piece object.
		 */
		Piece();
		
		/**
		 * @brief Construct a new Piece object.
		 * 
		 * @param path - File path to .obj file.
		 * @param pieceName - The name of the piece
		 * @param isWhite - If the piece is on white team.
		 */
		Piece(std::string const &path, std::string const &pieceName, bool isWhite);
	
		/**
		 * @brief Updates pice on every frame.
		 * 
		 * @param dt Deltatime between frames.
		 */
		void update(float dt);
		
		/**
		 * @brief Draw the piece to screen.
		 */
		void draw();
		
		/**
		 * @brief Setter for position.
		 * 
		 * @param position new position.
		 */
		void place(glm::vec3 position);
	
		/**
		 * @brief Getter for moves.
		 * @return moves represented as strings.
		 */
		auto getMoves() -> std::vector<std::string>;
	
		/**
		 * @brief Getter for name.
		 * @return name - Identifying the type.
		 */
		auto getName() -> std::string;
	
		/**
		 * @brief Getter for position.
		 * @return position.
		 */
		auto getPosition() -> glm::vec3;
		
		/**
		 * @brief Checks to see if first move is avalible.
		 * @return firstMove.
		 */
		bool isFirstMove();
	
		/**
		 * @brief Getter for isWhite
		 * @return isWhite
		 */
		bool isWhiteTeam();
	
		/**
		 * @brief Setter for isWhite.
		 * 
		 * @param team - True for white team.
		 */
		void setTeam(bool team);
	
		/**
		 * @brief Setter for selected.
		 * 
		 * @param select - Wether to select piece or not.
		 */
		void setSelected(bool select);
	
		/**
		 * @brief Setter for firstMove
		 * 
		 * @param fm wether the piece has made it's first move.
		 */
		void setFirstMove(bool fm);
	
	private:
		std::vector<std::string> move;		//!< Moves the piece can make.
		glm::vec3 pos;						//!< The world position of the piece.
		bool isWhite;						//!< The team the piece is on.
		bool selected;						//!< Whether the piece is selected.
		std::string name;					//!< Name of piece to identify type.
		bool firstMove;						//!< Whether first move has been made for the piece.
		modeler::Shader* shaderProgram;		//!< Shaderprogram used by piece for drawing.
	};
}