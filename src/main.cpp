#include "../header/glfw_setup.hpp"
#include "../header/global_function.hpp"
#include "../header/gl_setup.hpp"
#include "../header/piece.hpp"



int main(int argc, char const *argv[])
{	
	// OpenGL setup
	GLFWwindow* window = glfw_setup();

	// load stuff
	getMoves();
	Piece p = Piece("null", "Pawn");

	// start game


	return 0;
}
 