#pragma once
#include "piece.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <string>

/**
 * @brief 8x8 board represents pieces on each tile 
 */
class Board : Model{
public:
	
	/**
	 * @brief Board constructor
	 */
	Board(std::string const &path);
	
	/**
	 * @brief Move piece to the desired destination on the board
	 *
	 * @param indexI first index of the tiles/piece on the board
	 * @param indexJ second index of the tiles/piece on the board
	 * @param destinationI first index of tiles on the board
	 * @param destinationJ second index of tiles on the board
	 */
	void movePiece(int indexI, int indexJ, int destinationI, int destinationJ);
	
	/**
	 * @brief Draw the board and every piece found.
	 */
	void draw(float dt);

	/**
	 * @brief Convert piece moves to indecies for tiles[][].
	 * 
	 * @param indexI is the x location of the piece.
	 * @param indexJ is the y location of the piece.
	 * 
	 * @return returns a vector of new indecies that a piece can move to.
	 */
	auto moveToIndex(int indexI, int indexJ) -> std::vector<std::pair<int, int>>;

	/**
	 * @brief Uses bezeir curve to interpolate between three control points. 
	 * 
	 * @param a control point is current location.
	 * @param b control point is middle of point a and b-
	 * @param c control point is destination location-
	 * @param dt is delta time.
	 * @return a interpolated vector between 3 points.
	 */
	auto jumpCurve(glm::vec3 a, glm::vec3 b, glm::vec3 c, float dt) -> glm::vec3;

	/**
	 * @brief Does the calculation for bezeir curve.
	 * 
	 * @param p0 control point in 1D.
	 * @param p1 control point in 1D.
	 * @param dt is deltatime.
	 * @return a interpolated float between 2 points.
	 */
	auto getPoint(float p0, float p1, float dt) -> float;
	
	/**
	 * @brief Uses LERP to interpolate between two control points.
	 * 
	 * @param a control point is current location.
	 * @param b control point is destination location.
	 * @param dt is delta time.
	 * @return a interpolated vector between 2 points.
	 */
	auto lerp(glm::vec3 a, glm::vec3 b, float dt) -> glm::vec3;
	
	/**
	 * @brief Getter for tile
	 * @details [long description]
	 * @return [description]
	 */
	glm::vec2 getTileSize();
	glm::vec3 getPosition();
	glm::vec2 getEdge();
	std::pair<int, int> getSelected();
	
	bool hasPieceAt(int x, int y);
	bool hasWhitePieceAt(int x, int y);
	bool hasSelection();

	void setSelection(std::pair<int, int> selection);
	void clearSelection();
	void setAnimationTime(float animationTime);
	
	bool insideBoard(int i, int j);
	bool diffColor(int currentI, int currentJ, int targetI, int targetJ);


private:

	Piece* tiles[8][8];
	glm::vec2 tileSize;							//!< tile size
	glm::vec3 pos;								//!< center of board

	Shader* shaderProgram;

	float attenuationA = 1.0f;
	float attenuationB = 0.2f;
	float attenuationC = 0.0f;

	glm::vec3 lightSourcePosition = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec2 edge;								//!< board edges

	std::pair<int, int> selected;	
	float animationTime;
	std::pair<std::pair<int, int>, std::pair<int, int>> *animationTile = nullptr;
};