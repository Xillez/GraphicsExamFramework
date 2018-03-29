#include "../header/board.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Board::Board(std::string const &path) : Model(path){
	tiles = new glm::vec3* [8];
	for(int i = 0; i < 8; i++){
		tiles[i] = new glm::vec3[8];	
		for (int j = 0; j < 8; ++j)
		{
			tiles[i][j] = glm::vec3(i * offset, 0 , j * offset);
		}
	}

		// debug
	/*

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{

			std:: cout << i << " " << j << ", ";
			if(j==7) std::cout << std::endl;
		
		}
	}


	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{

			std:: cout << tiles[i][j].x << " " << tiles[i][j].y << " " << tiles[i][j].z << ", ";
			if(j==7) std::cout << std::endl;
		
		}
	}*/

	shaderProgram = new Shader("../shader/vertex.vert", "../shader/fragment.frag");
	shaderProgram->bind();

};


void Board::draw(){
	static float time = 0.0;
	time += .01;
	//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 projection = glm::perspective(3.14f / 3.0f, (GLfloat)1024 / (GLfloat)768, 0.1f, -10.0f);
	GLint viewID = glGetUniformLocation(shaderProgram->id(), "view");
	GLint projectionID = glGetUniformLocation(shaderProgram->id(), "projection");
	GLint modelID = glGetUniformLocation(shaderProgram->id(), "model");
	GLint normalMatrixID = glGetUniformLocation(shaderProgram->id(), "normalMatrix");
	glUniformMatrix4fv(viewID, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(projection));
	glm::mat4 modelm;
	modelm = glm::translate(modelm, glm::vec3(0.0f, -1.75f, -1.0f)); // translate it down so it's at the center of the scene
	modelm = glm::scale(modelm, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
															//glm::mat4 model = glm::rotate(glm::mat4(), time, glm::vec3(0, 1, 0));
	//model = glm::rotate(model, time, glm::vec3(0, 1, 0));														//ourShader.setMat4("model", model);
	glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(modelm));
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(view*modelm)));
	glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, glm::value_ptr(normalMatrix));
	
	Model::Draw(*shaderProgram); 
	 //printf("hello\t");

}