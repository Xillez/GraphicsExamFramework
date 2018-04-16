#include "../header/board.hpp"
#include "../header/global_function.hpp"
#include "../header/globalVar.hpp"
#include "../header/yaml_parser.hpp"
#include "../header/camera.hpp"	

#include <unordered_map>
#include <iostream>
#include <stdio.h>

extern GLFWwindow* window;
extern Camera* camera;
extern Board* chessBoard;
bool middleMousePressed = false;

std::unordered_map<std::string, std::vector<std::string>> moves;
glm::vec2 prevMousePos(0.0f, 0.0f);

glm::vec2 windowSize(){
	
	const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	return {videoMode->width * (relativeWindowSize.x / 100.0f),
		videoMode->height * (relativeWindowSize.y / 100.0f)};
}

void getMoves()
{
	YamlParser file("./resources/moves/move.yaml");
	std::vector<std::string> temp;
	std::pair<std::string, int> pieceCount = file.nextStringInt();

	file.nextLine();
	
	for (int i = 0; i < pieceCount.second; i++)
	{
		std::pair<std::string, std::string> pieceName = file.nextStringString();
		std::pair<std::string, int> moveCount = file.nextStringInt();
		file.nextLine();
		for (int j = 0; j < moveCount.second; j++)
		{
			temp.push_back(file.nextLine());
		}
		moves.insert(std::pair<std::string, std::vector<std::string>>(pieceName.second, temp));
		temp.clear();
	}

	for(auto i : moves)
	{
		for(auto v : i.second)
		{
			std::cout << i.first << " " << v << '\n';
		}
	}
}

void setup_EventHandling()
{
	glfwSetCursorPosCallback(window, ::OnMouseMove);
	glfwSetMouseButtonCallback(window, ::OnMouseClick);
}

void OnMouseMove(GLFWwindow *window, double xpos, double ypos)
{
	// Calculate 2d difference in 2d (window) mouse position
	// and update last pos to be current
	glm::vec2 deltaPos(xpos - prevMousePos.x, ypos - prevMousePos.y);
	prevMousePos = {xpos,ypos};

	if (!middleMousePressed)
		return;

	// Rotate camera around both rotational axes
	camera->rotateBy(deltaPos.x / 100.0f, (deltaPos.y * -1) / 100.f);
}

void OnMouseClick(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		glm::vec3 pointerPos = convertMousePosToWorld(xpos, ypos);

		std::pair<int, int> indecies(
			(int) ((-chessBoard->getPosition().x + (4 * chessBoard->getTileSize().x) + pointerPos.x) / chessBoard->getTileSize().x),
			(int) ((-chessBoard->getPosition().z + (4 * chessBoard->getTileSize().y) + pointerPos.z) / chessBoard->getTileSize().y));

		// If we are outside, ignore click!
		if ((indecies.first < 0 || indecies.first > 7) || (indecies.second < 0 || indecies.second > 7))
			return;

		if (chessBoard->hasPieceAt(indecies.first, indecies.second) && 
			!chessBoard->hasSelection())
		{
			chessBoard->setSelection(indecies);
			printf("Selected: %d : %d\n", indecies.first, indecies.second);
		}
		else if (chessBoard->hasSelection())
		{
			if (chessBoard->getSelected().first != indecies.first || 
				chessBoard->getSelected().second != indecies.second)
			{
				printf("Diff tile clicked, Piece moved to: %d : %d\n", indecies.first, indecies.second);
				
				chessBoard->movePiece(
					chessBoard->getSelected().first, chessBoard->getSelected().second, 
					indecies.first, indecies.second
				);
			}
			chessBoard->clearSelection();
		}

		//std::cout << (int)((-chessBoard->getPosition().x + (4 * chessBoard->getTileSize().x) + pointerPos.x) / chessBoard->getTileSize().x) << " : " 
		//	<< (int)((-chessBoard->getPosition().z + (4 * chessBoard->getTileSize().y) + pointerPos.z) / chessBoard->getTileSize().y) << "\n";
	}
	else if (button == GLFW_MOUSE_BUTTON_3 && action == GLFW_PRESS)
	{
		middleMousePressed = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_3 && action == GLFW_RELEASE)
	{
		middleMousePressed = false;
	}
}

glm::vec3 convertMousePosToWorld(double xpos, double ypos)
{
	glm::vec2 wSize = windowSize();
    GLfloat viewportY, z;

    viewportY = wSize.y - ypos;

    glReadPixels(xpos, viewportY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
    glm::vec3 mousePosInViewport = glm::vec3(xpos, viewportY, z);

    glm::mat4 viewMatrix = camera->getViewMatrix();
    glm::mat4 projectionMatrix = camera->getPerspectiveMatrix();
	return glm::unProject(mousePosInViewport, viewMatrix, projectionMatrix,
		glm::vec4(0.0f, 0.0f, wSize.x, wSize.y));
}