#include "../header/board.hpp"
#include "../header/camera.hpp"
#include "../class/ShaderManager.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include <iostream>

extern Camera* camera;

Board::Board(std::string const &path) : Model(path){
	// board position;
	pos.x = 0.0f;
	pos.y = 0.0f; //-1.75f; 
	pos.z = 0.0f; //-1.0f;

	// tile size;
	tileSize.x = 0.50f;
	tileSize.y = 0.50f;
	edge.x = 0.25f;
	edge.y = 0.25f;

	for(int k = 0; k  < 8; k++){
		for (int y = 0; y < 8; y++){
			tiles[k][y] = nullptr;
		}
	}

	for (int i = 0; i < 8; ++i){
		tiles[i][1] = new Piece("../asset/chessTemp/Pawn.obj", "Pawn", true);
		tiles[i][6] = new Piece("../asset/chessTemp/Pawn.obj", "Pawn", false);	
	}

	tiles[0][0] = new Piece("../asset/chessTemp/Rook.obj", "Rook", true);
	tiles[1][0] = new Piece("../asset/chessTemp/Knight.obj", "Horse", true);
	tiles[2][0] = new Piece("../asset/chessTemp/Bishop.obj", "Bishop", true);
	tiles[3][0] = new Piece("../asset/chessTemp/Queen.obj", "Queen", true);
	tiles[4][0] = new Piece("../asset/chessTemp/King.obj", "King", true);
	tiles[5][0] = new Piece("../asset/chessTemp/Bishop.obj", "Bishop", true);
	tiles[6][0] = new Piece("../asset/chessTemp/Knight.obj", "Horse", true);
	tiles[7][0] = new Piece("../asset/chessTemp/Rook.obj", "Rook", true);
	

	tiles[0][7] = new Piece("../asset/chessTemp/Rook.obj", "Rook", false);
	tiles[1][7] = new Piece("../asset/chessTemp/Knight.obj", "Horse", false);
	tiles[2][7] = new Piece("../asset/chessTemp/Bishop.obj", "Bishop", false);
	tiles[3][7] = new Piece("../asset/chessTemp/King.obj", "King", false);
	tiles[4][7] = new Piece("../asset/chessTemp/Queen.obj", "Queen", false);
	tiles[5][7] = new Piece("../asset/chessTemp/Bishop.obj", "Bishop", false);
	tiles[6][7] = new Piece("../asset/chessTemp/Knight.obj", "Horse", false);
	tiles[7][7] = new Piece("../asset/chessTemp/Rook.obj", "Rook", false);

	float offset = 1.15f;//3.14f / 6.0f;
	
	float x, y, z;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(tiles[i][j] != nullptr){
				x = pos.x + (-tileSize.x*4 + edge.x + (tileSize.x * i));//+ (-4 * offset); // + (j * offset + (offset / 2));
				y = 0.0f + pos.y;//-1.15f;
				z = pos.y + (-tileSize.y*4 + edge.y + (tileSize.y * j));//+ (-3 * offset);//+ (i * offset);

				std::cout << "i:" << i << ", j:" << j << '\n';
				std::cout << "x: " << x << ", y:" << y << ", z:" << z << '\n'; 
				tiles[i][j]->place(x, y, z);
				//	+x --- right, -x --- left
				//	+y --- up,   -y --- down
				//  +z ---- front, -z --- back
			}
		}
	}

	extern ShaderManager* shaderManager;
	shaderProgram = shaderManager->getShader(std::vector<std::pair<GLenum, std::string>>{
		{GL_VERTEX_SHADER, "../shader/vertex.vert"},
		{GL_FRAGMENT_SHADER, "../shader/fragment.frag"},
	});

};

void Board::movePiece(int indexI, int indexJ, float destinationI, float destinationJ){
	tiles[indexI][indexJ]->place(
							(-4 * (3.14 / 10)) + (destinationJ * (3.14 / 10)) + ((3.14 / 10) / 2),
							 pos.y, 
							 0.0f + (destinationI * (3.14 / 10)));
}

void Board::draw(){
	shaderProgram->bind();

	static float time = 0.0;
	time += .01;

	//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera->getViewMatrix(); //glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//glm::mat4 view = glm::lookAt(glm::vec3(0, 5, 0), glm::vec3(0, 4, 0), glm::vec3(0, 0, -1));
	glm::mat4 projection = camera->getPerspectiveMatrix();//glm::perspective(3.14f / 3.0f, (GLfloat)1024 / (GLfloat)768, 0.1f, -10.0f);

	// Rotate light for effect
	lightSourcePosition.x = sin(glfwGetTime()) * 3.0f;
	lightSourcePosition.z = cos(glfwGetTime()) * 2.0f;
	lightSourcePosition.y = 5.0 + cos(glfwGetTime()) * 1.0f;

	std::map<std::string, GLuint> uniforms = shaderProgram->getUniform(	std::map<std::string, GLchar*>({
		{"viewID", "view"},
		{"projectionID", "projection"},
		{"modelID", "model"},
		{"normalMatrixID", "normalMatrix"},
		{"lightSourcePositionID","lightSourcePosition"},
		{"camPosID", "CamPos"},
		{"attenuationAID", "attenuationA"},
		{"attenuationBID", "attenuationB"},
		{"attenuationCID", "attenuationC"},
		{"lightColorID", "lightColor"}
	}));
	// TODO: get light information from camera / view.
	glUniform1f(uniforms["attenuationAID"], attenuationA);
	glUniform1f(uniforms["attenuationBID"], attenuationB);
	glUniform1f(uniforms["attenuationCID"], attenuationC);
	glUniform3fv(uniforms["lightColorID"], 1, value_ptr(lightColor));
	glUniform3fv(uniforms["lightSourcePositionID"], 1, value_ptr(lightSourcePosition));
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

	glUniform3fv(uniforms["camPosID"], 1, value_ptr(position));												//glm::mat4 model = glm::rotate(glm::mat4(), time, glm::vec3(0, 1, 0));

	glUniformMatrix4fv(uniforms["viewID"], 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(uniforms["projectionID"], 1, GL_FALSE, glm::value_ptr(projection));
	glm::mat4 modelm;
	modelm = glm::translate(modelm, pos); // translate it down so it's at the center of the scene
	//modelm = glm::translate(modelm, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	modelm = glm::scale(modelm, glm::vec3(0.4f, 0.4f, 0.4f));	// it's a bit too big for our scene, so scale it down
	//modelm = glm::rotate(modelm, time, glm::vec3(0, 1, 0));	
													//ourShader.setMat4("model", model);
	glUniformMatrix4fv(uniforms["modelID"], 1, GL_FALSE, glm::value_ptr(modelm));
	
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(view*modelm)));
	glUniformMatrix3fv(uniforms["normalMatrixID"], 1, GL_FALSE, glm::value_ptr(normalMatrix));
	
	Model::Draw(*shaderProgram); 
	 //printf("hello\t");

	shaderProgram->unbind();

	// TODO: draw pieces

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(tiles[i][j] != nullptr){
				tiles[i][j]->draw();
			}
		}
	}
}

glm::vec2 Board::getTileSize()
{
	return this->tileSize;
}

glm::vec3 Board::getPosition()
{
	return this->pos;
}

glm::vec2 Board::getEdge()
{
	return this->edge;
}