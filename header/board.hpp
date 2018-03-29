#pragma once
#include "../class/model.hpp"
#include <string>
#include <glm/glm.hpp>

class Board : Model{
public:
	Board(std::string const &path);

	void draw();

private:
	glm::vec3** tiles;
	Shader* shaderProgram;
	float offset = 10.0f;
};