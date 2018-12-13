#include <Engine\Renderer.h>
#include "SpriteComponent.h"

SpriteComponent::~SpriteComponent()
{
	freeSprite();
}

bool SpriteComponent::loadSprite(
	ASGE::Renderer* renderer, const std::string& texture_file_name)
{
	freeSprite();
	sprite = renderer->createRawSprite();
	if (sprite->loadTexture(texture_file_name))
	{
		return true;
	}

	freeSprite();
	return false;
}

void SpriteComponent::freeSprite()
{
	if (sprite)
	{
		delete sprite;
		sprite = nullptr;
	}
}

ASGE::Sprite* SpriteComponent::getSprite()
{
	return sprite;
}

void SpriteComponent::spriteCenter(float x, float y)
{
	sprite->xPos(x - sprite->width() / 2);
	sprite->yPos(y - sprite->height() / 2);
}

float SpriteComponent::xCenter()
{
	return (sprite->xPos() + (sprite->width() / 2));
}

float SpriteComponent::yCenter()
{
	return (sprite->yPos() + (sprite->height() / 2));
}

rect SpriteComponent::getBoundingBox() const
{
	rect bounding_box;
	bounding_box.x = sprite->xPos();
	bounding_box.y = sprite->yPos();
	bounding_box.length = sprite->width();
	bounding_box.height = sprite->height();

	return bounding_box;
}

rect SpriteComponent::bBT() const
{
	rect bounding_box;
	bounding_box.x = sprite->xPos() + 10;
	bounding_box.y = sprite->yPos() - 5;
	bounding_box.length = sprite->width() - 15;
	bounding_box.height = 5;

	return bounding_box;
}

rect SpriteComponent::bBR() const
{
	rect bounding_box;
	bounding_box.x = sprite->xPos() + sprite->width();
	bounding_box.y = sprite->yPos() + 3;
	bounding_box.length = 5;
	bounding_box.height = sprite->height() - 1;

	return bounding_box;
}

rect SpriteComponent::bBL() const
{
	rect bounding_box;
	bounding_box.x = sprite->xPos() - 5;
	bounding_box.y = sprite->yPos() + 3;
	bounding_box.length = 5;
	bounding_box.height = sprite->height() - 1;

	return bounding_box;
}

rect SpriteComponent::bBB() const
{
	rect bounding_box;
	bounding_box.x = sprite->xPos() + 5;
	bounding_box.y = sprite->yPos() + sprite->height();
	bounding_box.length = sprite->width() - 5;
	bounding_box.height = sprite->height() + 5;

	return bounding_box;
}