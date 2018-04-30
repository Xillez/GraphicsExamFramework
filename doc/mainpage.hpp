/*! \mainpage Chess3d
 *	
 *	\author Eldar Hauge Torkelsen - 473180 - eldarht@stud.ntnu.no
 *	\author Kent Wincent Holt - 473209 - kentwh@stud.ntnu.no
 *	\author Zohaib Butt - 473219 - zohaibb@stud.ntnu.no
 *	
 * \section intro_sec Introduction
 *
 * Handin for IMT2531 - Graphics programming.
 * 
 * A lightweight chess engine, using OpengGL as Graphics API.
 * 
 * \section install_sec Installation
 *	1. Install linux.
 *	2. From repository root, run mkdir build && cd build.
 *	3. Build the program: 
 *	```Shell
 *	cmake .. && make
 *	```
 *	4. Run the executable:
 *	``` 
 *	./bin/Chess3D.
 *	```
 * \section feature_sec Features
 *
 *	- Playable chess with 3d graphics.
 *	- Pieces can be moved using the mouse.
 *	- Rotate view with middle mouse button and WASD.
 *	- Lighting.
 *	
 *	\todo 
 *	- Parsing text that can create moves with functionality to validate the move based on current state of board.
 *	- Highlighting for available moves on selected piece, using move parser and geometry shader.
 *	- Terain / environment around chessboard.
 *	- New gamemode for chessboard using positions in 3d (3DChess).
 *	- Display past moves using chess notation.
 */