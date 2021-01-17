#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation
{
private:
	//Variables
	sf::Vector2u start;
	sf::Vector2u end;
	sf::Vector2u current;
	sf::IntRect uvRect;

	float totalTime;
	float switchTime;

public:
	//Constructors/Destructors
	Animation();
	Animation(sf::Vector2u start, sf::Vector2u end, sf::Vector2u size, float switchTime);

	//Accessors


	//Modifiers
	void setSwitchTime(float switchTime);

	//Functions
	void reset();
	void update(sf::Sprite* sprite, const float deltaTime, const bool flip = false);
	void apply(sf::Sprite* sprite, const bool flip = false);
};

#endif // !ANIMATION_H