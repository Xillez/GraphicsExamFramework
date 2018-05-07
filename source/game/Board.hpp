#pragma once
#include "Piece.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <string>

/**
 * @brief Container for content specific to chess game.
 */
namespace game{
	/**
	 * @brief 8x8 chessboard managing pieces.
	 */
	class Board : modeler::Model{
	public:
		
		/**
		 * @brief Board constructor.
		 */
		Board(std::string const &path);
		
		/**
		 * @brief Move piece to the desired destination on the board.
		 *
		 * @param indexI - First index of the tiles/piece on the board.
		 * @param indexJ - Second index of the tiles/piece on the board.
		 * @param destinationI - First index of tiles on the board.
		 * @param destinationJ - Second index of tiles on the board.
		 */
		void movePiece(int indexI, int indexJ, int destinationI, int destinationJ);
		
		/**
		 * @brief updates state for next frame.
		 * 
		 * @param dt - Deltatime since last frame.
		 */
		void update(float dt);

		/**
		 * @brief Draw the board and every piece found.
		 */
		void draw();
	
		/**
		 * @brief Convert piece moves to indecies for tiles[][].
		 * 
		 * @param indexI - The x location of the piece.
		 * @param indexJ - The y location of the piece.
		 * 
		 * @return A vector of new indecies that a piece can move to.
		 */
		auto moveToIndex(int indexI, int indexJ) -> std::vector<std::pair<int, int>>;
	
		/**
		 * @brief Uses bezeir curve to interpolate between three control points. 
		 * 
		 * @param a - Control point is current location.
		 * @param b - Control point is middle of point a and b.
		 * @param c - Control point is destination location.
		 * @param dt - Delta time.
		 * @return Interpolated vector between 3 points.
		 */
		auto jumpCurve(glm::vec3 a, glm::vec3 b, glm::vec3 c, float dt) -> glm::vec3;
	
		/**
		 * @brief Does the calculation for bezeir curve.
		 * 
		 * @param p0 - Control point in 1D.
		 * @param p1 - Control point in 1D.
		 * @param dt - Deltatime.
		 * @return Interpolated float between 2 points.
		 */
		auto getPoint(float p0, float p1, float dt) -> float;
		
		/**
		 * @brief Uses LERP to interpolate between two control points.
		 * 
		 * @param a - Control point is current location.
		 * @param b - Control point is destination location.
		 * @param dt - Delta time.
		 * @return Interpolated vector between 2 points.
		 */
		auto lerp(glm::vec3 a, glm::vec3 b, float dt) -> glm::vec3;
		
		/**
		 * @brief Getter for tileSize.
		 * @return tileSize.
		 */
		glm::vec2 getTileSize();
	
		/**
		 * @brief Getter for position.
		 * @return position.
		 */
		glm::vec3 getPosition();
	
		/**
		 * @brief Getter for selected.
		 * @return selected.
		 */
		std::pair<int, int> getSelected();
		
		/**
		 * @brief Check if there is a piece at the board position.
		 * 
		 * @param x - Character row of board.
		 * @param y - Numbered row of board.
		 * 
		 * @return True of there is a piece at the tile.
		 */
		bool hasPieceAt(int x, int y);
	
		/**
		 * @brief Check if there is a white piece at
		 * 
		 * @param x - Character row of board.
		 * @param y - Numbered row of board.
		 * 
		 * @return -1 if no piece, 0 if black and 1 if white.
		 */
		int pieceColorAt(int x, int y);
	
		/**
		 * @brief Check if a piece is selected.
		 * @return True if a piece is selected.
		 */
		bool hasSelection();
	
		/**
		 * @brief Setter for selected.
		 * 
		 * @param selection The tile of the piece to select.
		 */
		void setSelection(std::pair<int, int> selection);
	
		/**
		 * @brief Un select selection.
		 */
		void clearSelection();
		
		/**
		 * @brief Check if given tile is inside board.
		 * 
		 * @param x Character row of board.
		 * @param y Numbered row of board.
		 * 
		 * @return True if tile is inside board.
		 */
		bool insideBoard(int x, int y);
	
		/**
		 * @brief Check if current is of different team than target.
		 * 
		 * @param currentX Character row of board for first piece.
		 * @param currentY Numbered row of board for first piece.
		 * @param targetX Character row of board for second piece.
		 * @param targetY Numbered row of board for second piece.
		 * 
		 * @return True if current piece is on different team from target.
		 */
		bool diffColor(int currentX, int currentY, int targetX, int targetY);
	
	private:
	
		Piece* tiles[8][8];								//!< Locations on the board.
	
		glm::vec2 tileSize;								//!< Tile size.
		glm::vec2 edge;									//!< Board edges.
		glm::vec3 position;								//!< Origin of board.
	
		std::pair<int, int> selected;					//!< Tile for selected piece.
	
		modeler::Shader* shaderProgram;					//!< Shaderprogram used by board for drawing.
	
		float animationTime;							//!< How long current animation has come.
		//! Tile of the piece currently animating and where it is going. 
		std::pair<std::pair<int, int>, std::pair<int, int>> *animationTile = nullptr;
	
		//! Converter for chessboard notation of character row to board array x index.
		enum{A = 0, B, C, D, E, F, G, H};

		bool isWhiteTurn = true; 						//!< Indicates whos turn it is to move.
	};
}