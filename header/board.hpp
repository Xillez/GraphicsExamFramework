#pragma once
#include "piece.hpp"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
class Board : Model{
public:
	Board(std::string const &path);

	void draw();

private:
	Piece* tiles[8][8];
	Shader* shaderProgram;
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//glm::mat4 view = glm::lookAt(glm::vec3(0, 5, 0), glm::vec3(0, 4, 0), glm::vec3(0, 0, -1));
	glm::mat4 projection = glm::perspective(3.14f / 3.0f, (GLfloat)1024 / (GLfloat)768, 0.1f, -10.0f);
	
	glm::vec3 lightSourcePosition = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
};