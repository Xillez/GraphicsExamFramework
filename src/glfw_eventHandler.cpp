#include "../header/glfw_eventHandler.hpp"

EventHandler::EventHandler()
{
	this->window = nullptr;
}

void EventHandler::setup_eventHandler(GLFWwindow* window)
{
	this->window = window;
	glfwSetCursorPosCallback(this->window, this->onMouseMove);
	glfwSetMouseButtonCallback(this->window, this->onMouseClick);
}

/*void EventHandler::onKeyboardInput()
{

}*/

void EventHandler::onMouseMove(GLFWwindow* window, double xpos, double ypos)
{
	std::cout << xpos << ":" << ypos << "\n";
}

void EventHandler::onMouseClick(GLFWwindow* window, int button, int action, int mods)
{
	std::cout << button << ":" << action << ":" << mods << "\n";
}

/*void EventHandler::onResume()
{

}*/

/*void EventHandler::onPause()
{

}*/

/*void EventHandler::onTick()
{

}*/
