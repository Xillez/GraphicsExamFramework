//#include "../header/gl_setup.hpp"
#include "../header/piece.hpp"
//#include "../header/glfw_setup.hpp"
#include "../header/errorHandler.hpp"
#include "../header/globalVar.hpp"
#include "../header/yamlParser.hpp"



// Global Function

void getMoves() {
	yamlParser file("./resources/moves/move.yaml");
	std::vector<std::string> temp;
	std::pair<std::string, int> pieceCount = file.nextStringInt();

	file.nextLine();
	
	for (int i = 0; i < pieceCount.second; i++) {
		std::pair<std::string, std::string> pieceName = file.nextStringString();
		std::pair<std::string, int> moveCount = file.nextStringInt();
		file.nextLine();
		for (int j = 0; j < moveCount.second; j++) {
			temp.push_back(file.nextLine());
		}
		moves.insert(std::pair<std::string, std::vector<std::string>>(pieceName.second, temp));
		temp.clear();
	}

	for (auto v : moves) {
		for (auto m : v.second) {
			std::cout << v.first << ": " << m << '\n';
		}
	}
}



int main(int argc, char const *argv[])
{
	
	// setup gl
	
	//window = glfw_setup();

	// load stuff
	getMoves();
	Piece p = Piece("null", "Pawn");
	// start game


	system("Pause");
	return 0;
}
 