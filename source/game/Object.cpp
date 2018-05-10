#include "Object.hpp"
#include "../modeler/ShaderManager.hpp"
#include "../components/GraphicsComponent.hpp"

extern modeler::ShaderManager* shaderManager;
float rotationTime = 0.0f;

game::Object::Object()
{

	this->position = glm::vec3(2.0f, 0.0f, 0.0f);

	this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	this->acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
}

auto game::Object::registerComponent(components::IComponent* component) -> bool
{
	// If this is a valid component
	if (component)
	{
		// Add parent / initialize with current obect as parent
		component->init(this);
		// Add it to current objects component list
		this->componentList.push_back(component);
	}

	// Tell whether it was added or not
	return (component);
}

auto game::Object::update(float dt) -> void
{
	
}

auto game::Object::draw(float dt) -> void
{
	model = glm::mat4();
	rotationTime += dt / 10.0f;
	model = glm::translate(model, this->position); // Translate it down so it's at the center of the scene.
	//printf("%f, %f, %f\n",position.x, position.y, position.z );
	model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));	
	model = glm::rotate(model, rotationTime, glm::vec3(0.0f, 1.0f, 0.0f));

	if (this->componentList.at(0))
		this->componentList.at(0)->draw();
}

auto game::Object::getModelMatrix() -> glm::mat4{
	return this->model;
}

auto game::Object::setPos(glm::vec3 newPos) -> void {
	this->position = newPos;
}