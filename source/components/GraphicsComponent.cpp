#include "GraphicsComponent.hpp"
#include "../modeler/Renderer.hpp"

extern modeler::Renderer* render; 

components::GraphicsComponent::GraphicsComponent(std::string const &modelPath) : IComponent()
{
	render->registerModel(modelPath);
	this->path = modelPath;
}

// Virtual
auto components::GraphicsComponent::init(game::Object* parent) -> void
{
	this->parent = parent;
}

// Virtual
auto components::GraphicsComponent::update(float dt) -> void
{

}

// Virtual
auto components::GraphicsComponent::draw() -> void
{
	//this->model->Draw(shader);
	render->draw(path, parent);
}

// Virtual
auto components::GraphicsComponent::getType() -> int
{
	return GRAPHICS_COMPONENT;
}