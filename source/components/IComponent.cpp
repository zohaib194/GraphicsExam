#include "IComponent.hpp"

components::IComponent::IComponent()
{
	//
}

auto components::IComponent::init(game::HeightMap* parent) -> void
{
	this->parent = parent;
}