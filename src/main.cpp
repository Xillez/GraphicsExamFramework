#include "../header/gl_setup.hpp"
#include "../header/piece.hpp"
#include "../header/glfw_setup.hpp"
#include "../header/errorHandler.hpp"
#include "../header/global_function.hpp"



// Global Function



int main(int argc, char const *argv[])
{
	
	// setup gl
	
	window = glfw_setup();

	// load stuff
	getMoves();
	Piece p = Piece("null", "Pawn");
	// start game


	system("Pause");
	return 0;
}
 