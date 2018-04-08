#pragma once
#include "piece.hpp"
#include <string>
class Board : Model{
public:
	Board(std::string const &path);

	void draw();

private:
	Piece* tiles[8][8];
	Shader* shaderProgram;
	float offset = 10.0f;
};