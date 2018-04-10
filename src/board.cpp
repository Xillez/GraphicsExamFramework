#include "../header/board.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Board::Board(std::string const &path) : Model(path){

	for(int z = 0; z  < 8; z++){
		for (int y = 0; y < 8; y++){
			tiles[z][y] = nullptr;
		}
	}
	for (int i = 0; i < 8; ++i){
		tiles[1][i] = new Piece("../asset/chessTemp/Pawn.obj", "Pawn", true);
		tiles[6][i] = new Piece("../asset/chessTemp/Pawn.obj", "Pawn", false);
		
	}

	tiles[0][0] = new Piece("../asset/chessTemp/Rook.obj", "Rook", true);
	tiles[0][1] = new Piece("../asset/chessTemp/Knight.obj", "Horse", true);
	tiles[0][2] = new Piece("../asset/chessTemp/Bishop.obj", "Bishop", true);
	tiles[0][3] = new Piece("../asset/chessTemp/Queen.obj", "Queen", true);
	tiles[0][4] = new Piece("../asset/chessTemp/King.obj", "King", true);
	tiles[0][5] = new Piece("../asset/chessTemp/Bishop.obj", "Bishop", true);
	tiles[0][6] = new Piece("../asset/chessTemp/Knight.obj", "Horse", true);
	tiles[0][7] = new Piece("../asset/chessTemp/Rook.obj", "Rook", true);
	

	tiles[7][0] = new Piece("../asset/chessTemp/Rook.obj", "Rook", false);
	tiles[7][1] = new Piece("../asset/chessTemp/Knight.obj", "Horse", false);
	tiles[7][2] = new Piece("../asset/chessTemp/Bishop.obj", "Bishop", false);
	tiles[7][3] = new Piece("../asset/chessTemp/King.obj", "King", false);
	tiles[7][4] = new Piece("../asset/chessTemp/Queen.obj", "Queen", false);
	tiles[7][5] = new Piece("../asset/chessTemp/Bishop.obj", "Bishop", false);
	tiles[7][6] = new Piece("../asset/chessTemp/Knight.obj", "Horse", false);
	tiles[7][7] = new Piece("../asset/chessTemp/Rook.obj", "Rook", false);

	float offset = 3.14 / 10;
	
	float x, y, z;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(tiles[i][j] != nullptr){
				x = (-4 * offset) + (j * offset + (offset / 2));
				y = -1.15f ;
				z = 0.0f + (i * offset);


				std::cout << "i:" << i << ", j:" << j << '\n';
				std::cout << "x: " << x << ", y:" << y << ", z:" << z << '\n'; 
				tiles[i][j]->place(x, y, z);
				//	+x --- right, -x --- left
				//	+y --- up,   -y --- down
				//  +z ---- front, -z --- back
			}
		}
	}

	shaderProgram = new Shader("../shader/vertex.vert", "../shader/fragment.frag");
	shaderProgram->bind();

};


void Board::draw(){
	static float time = 0.0;
	time += .01;
	//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//glm::mat4 view = glm::lookAt(glm::vec3(0, 5, 0), glm::vec3(0, 4, 0), glm::vec3(0, 0, -1));
	glm::mat4 projection = glm::perspective(3.14f / 3.0f, (GLfloat)1024 / (GLfloat)768, 0.1f, -10.0f);
	std::map<std::string, GLuint> uniforms = shaderProgram->getUniform(	std::map<std::string, GLchar*>({
		{"viewID", "view"},
		{"projectionID", "projection"},
		{"modelID", "model"},
		{"normalMatrixID", "normalMatrix"},
	}));

	glUniformMatrix4fv(uniforms["viewID"], 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(uniforms["projectionID"], 1, GL_FALSE, glm::value_ptr(projection));
	glm::mat4 modelm;
	modelm = glm::translate(modelm, glm::vec3(0.0f, -1.75f, -1.0f)); // translate it down so it's at the center of the scene
	//modelm = glm::translate(modelm, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	modelm = glm::scale(modelm, glm::vec3(0.4f, 0.4f, 0.4f));	// it's a bit too big for our scene, so scale it down
															//glm::mat4 model = glm::rotate(glm::mat4(), time, glm::vec3(0, 1, 0));
	//modelm = glm::rotate(modelm, time, glm::vec3(0, 1, 0));														//ourShader.setMat4("model", model);
	glUniformMatrix4fv(uniforms["modelID"], 1, GL_FALSE, glm::value_ptr(modelm));
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(view*modelm)));
	glUniformMatrix3fv(uniforms["normalMatrixID"], 1, GL_FALSE, glm::value_ptr(normalMatrix));
	
	Model::Draw(*shaderProgram); 
	 //printf("hello\t");


	// TODO: draw pieces
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(tiles[i][j] != nullptr){
				tiles[i][j]->draw();
			}
		}
	}
	
}