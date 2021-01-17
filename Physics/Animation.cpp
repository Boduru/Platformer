#include "stdafx.h"

Animation::Animation() : Animation(sf::Vector2u(0, 0), sf::Vector2u(0, 0), sf::Vector2u(0, 0), 0.0f)
{
}

//___________Constructors/Destructors___________
Animation::Animation(sf::Vector2u start, sf::Vector2u end, sf::Vector2u size, float switchTime)
	: start(start), end(end), current(start),
	switchTime(switchTime), totalTime(0)
{
	this->uvRect = sf::IntRect(start.x, start.y, size.x, size.y);
}

//___________Accessors___________

//___________Modifiers___________
void Animation::setSwitchTime(const float switchTime)
{
	this->switchTime = switchTime;
}

//___________Functions___________
void Animation::update(sf::Sprite* sprite, const float deltaTime, const bool flip)
{
	this->totalTime += deltaTime;

	if (this->totalTime >= this->switchTime) {
		this->totalTime -= this->switchTime;

		this->current.x++;

		if (this->current.x >= this->end.x)
			this->current.x = start.x;

		if (this->current.y >= this->end.y)
			this->current.y = start.y;
	}

	this->uvRect.left = this->current.x * this->uvRect.width;
	this->uvRect.top = this->current.y * this->uvRect.height;

	this->apply(sprite, flip);
}

void Animation::apply(sf::Sprite* sprite, const bool flip)
{
	if (flip)
		sprite->setTextureRect(sf::IntRect(this->uvRect.left + this->uvRect.width, this->uvRect.top, -this->uvRect.width, this->uvRect.height));
	else
		sprite->setTextureRect(this->uvRect);
}

void Animation::reset()
{
	this->current.x = this->start.x;
	this->current.y = this->start.y;
	this->uvRect.left = this->start.x;
	this->uvRect.top = this->start.y;
}