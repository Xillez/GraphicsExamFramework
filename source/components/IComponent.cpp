#include "IComponent.hpp"

components::IComponent::IComponent()
{
	//
}

auto components::IComponent::init(game::Object* parent) -> void
{
	this->parent = parent;
}