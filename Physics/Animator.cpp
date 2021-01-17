#include "stdafx.h"

Animator::Animator() : Animator(nullptr, nullptr, sf::Vector2u(0, 0))
{

}

//Constructors/Destructors
Animator::Animator(sf::Texture* texture, sf::Sprite* sprite, sf::Vector2u offset)
	: textureSheet(texture), sprite(sprite), imgOffset(offset)
{
	this->calculateCellSize();
}

Animator::~Animator()
{
	//delete this->textureSheet;
	//delete this->sprite;
}

//Accessors
sf::Vector2u Animator::getImageOffsets()
{
	return this->imgOffset;
}

sf::Vector2u Animator::getCellSize()
{
	return this->cellSize;
}

//Modifiers
void Animator::setSwitchTime(std::string name, float switchTime)
{
	if (this->isAvailable(name))
		this->animations[name].setSwitchTime(switchTime);
}

//Functions
bool Animator::isAvailable(std::string name)
{
	return this->animations.find(name) != this->animations.end() && this->textureSheet != nullptr;
}

void Animator::calculateCellSize()
{
	if (this->imgOffset.x + this->imgOffset.y != 0)
	{
		this->cellSize.x = static_cast<int>(this->textureSheet->getSize().x / static_cast<float>(this->imgOffset.x));
		this->cellSize.y = static_cast<int>(this->textureSheet->getSize().y / static_cast<float>(this->imgOffset.y));
	}
}

void Animator::addAnimation(std::string name, unsigned start_x, unsigned end_x, unsigned start_y, unsigned end_y, float switch_time)
{
	Animation anim(sf::Vector2u(start_x, start_y), sf::Vector2u(end_x, end_y), sf::Vector2u(this->cellSize.x, this->cellSize.y), switch_time);
	this->animations[name] = anim;
}

void Animator::play(std::string name, const float deltatime, const bool flip)
{
	if (this->isAvailable(name))
		this->animations[name].update(this->sprite, deltatime, flip);
}

void Animator::reset(std::string name)
{
	if (this->isAvailable(name))
		this->animations[name].reset();
}