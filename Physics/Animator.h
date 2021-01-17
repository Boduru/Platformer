#ifndef ANIMATOR_H
#define ANIMATOR_H

class Animation;

class Animator
{
private:
	//Variables
	std::map<std::string, Animation> animations;
	sf::Texture* textureSheet;
	sf::Sprite* sprite;
	sf::Vector2u cellSize;
	sf::Vector2u imgOffset;

public:
	//Costructors/Destructors
	Animator();
	Animator(sf::Texture* texture, sf::Sprite* sprite, sf::Vector2u offset);
	virtual ~Animator();

	//Accessors
	sf::Vector2u getImageOffsets();
	sf::Vector2u getCellSize();

	//Modifiers
	void setSwitchTime(std::string name, float switchTime);

	//Functions
	bool isAvailable(std::string name);
	void calculateCellSize();
	void addAnimation(std::string name, unsigned start_x, unsigned end_x, unsigned start_y, unsigned end_y, float switch_time);
	void play(std::string name, const float deltatime, const bool flip = false);
	void reset(std::string name);
};

#endif // !ANIMATOR_H