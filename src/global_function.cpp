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
	//std::cout << xpos << ":" << ypos << "\n";
    GLfloat winY, z;

    winY = (GLfloat)768 - ypos;

    glReadPixels(xpos, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
    glm::vec3 screen = glm::vec3(xpos, winY, z);

    glm::mat4 viewMatrix = glm::lookAt(
		glm::vec3(0, 5, 0), glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));
    glm::mat4 ProjectionMatrix = glm::perspective(
        45.0f, (GLfloat)1024 / (GLfloat)768, 0.1f, 10.0f);
	glm::vec3 pos3D;
    pos3D = glm::unProject(screen, viewMatrix, ProjectionMatrix,
		glm::vec4(0, 0, (GLfloat)1024, (GLfloat)768));

	printf("%f : %f : %f\n", pos3D.x, pos3D.y, pos3D.z);
}