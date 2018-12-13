#include <Engine\Renderer.h>
#include "GameObject.h"

GameObject::~GameObject()
{
	freeSpriteComponent();
}

void GameObject::render(ASGE::Renderer* renderer)
{
	renderer->renderSprite(*sprite_component->getSprite());
}

bool GameObject::addSpriteComponent(
	ASGE::Renderer* renderer, const std::string& texture_file_name)
{
	freeSpriteComponent();

	sprite_component = new SpriteComponent();
	if (sprite_component->loadSprite(renderer, texture_file_name))
	{
		return true;
	}

	freeSpriteComponent();
	return false;
}

void  GameObject::freeSpriteComponent()
{
	delete sprite_component;
	sprite_component = nullptr;
}


SpriteComponent* GameObject::spriteComponent()
{
	return sprite_component;
}

void GameObject::setTag(std::string tag_name)
{
	tag = tag_name;
}

std::string GameObject::getTag()
{
	return tag;
}

void GameObject::setTexture(std::string texture_name)
{
	texture = texture_name;
}

std::string GameObject::getTexture()
{
	return texture;
}

//void GameObject::dampness(float value)
//{
//	damp = value;
//	if (damp > 150)
//	{
//		spriteComponent()->getSprite()->colour(ASGE::COLOURS::LIGHTSKYBLUE);
//		damp = 150;
//	}
//	if (damp > 100 && damp < 110)
//	{
//		spriteComponent()->getSprite()->colour(ASGE::COLOURS::LIGHTSTEELBLUE);
//	}
//	if (damp > 45 && damp < 46)
//	{
//		spriteComponent()->getSprite()->colour(ASGE::COLOURS::LIGHTBLUE);
//	}
//	if (damp > 25 && damp < 26)
//	{
//		spriteComponent()->getSprite()->colour(ASGE::COLOURS::ALICEBLUE);
//	}
//	if (damp <= 0)
//	{
//		spriteComponent()->getSprite()->colour(ASGE::COLOURS::WHITE);
//		damp = 0;
//	}
//}
//
//float GameObject::dampness()
//{
//	return damp;
//}
//
//void GameObject::drag(bool value)
//{
//	dragging = value;
//}
//
//bool GameObject::drag()
//{
//	return dragging;
//}