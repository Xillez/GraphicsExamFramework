#include "GraphicsComponent.hpp"

components::GraphicsComponent::GraphicsComponent(std::string const &modelPath) : IComponent()
{
	this->model = new modeler::Model(modelPath);
}

// Virtual
auto components::GraphicsComponent::update(float dt) -> void
{

}

// Virtual
auto components::GraphicsComponent::draw(modeler::Shader shader) -> void
{
	this->model->Draw(shader);
}

// Virtual
auto components::GraphicsComponent::getType() -> int
{
	return GRAPHICS_COMPONENT;
}