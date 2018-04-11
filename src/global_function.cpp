#include "../header/global_function.hpp"
#include "../header/yaml_parser.hpp" 		
#include <iostream>
#include <stdio.h>

std::unordered_map<std::string, std::vector<std::string>> moves; 

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
	extern GLFWwindow* window;
	glfwSetCursorPosCallback(window, ::OnMouseMove);
	//glfwSetMouseButtonCallback(this->window, [](GLFWwindow* window, int button, int action, int mods) { std::cout << button << ":" << action << ":" << mods << "\n"; });
}

void OnMouseMove(GLFWwindow *window, double xpos, double ypos)
{
	std::cout << xpos << ":" << ypos << "\n";
    GLint viewport[4];
    GLfloat winY, z;
    glGetIntegerv(GL_VIEWPORT, viewport);

    winY = viewport[3] - ypos;

    glReadPixels(xpos, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
    glm::vec3 screen = glm::vec3(xpos, winY, z);

    glm::mat4 viewMatrix = glm::lookAt(
		glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 ProjectionMatrix = glm::perspective(
        45.0f, (GLfloat)viewport[2] / (GLfloat)viewport[3], 0.1f, 500.0f);
	glm::vec3 pos3D;
    pos3D = glm::unProject(screen, viewMatrix, ProjectionMatrix,
		glm::vec4(viewport[0], viewport[1], viewport[2], viewport[3]));

	printf("%f : %f : %f\n", pos3D.x, pos3D.y, pos3D.z);
}