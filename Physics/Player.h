#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Entity;

class Player : public Entity
{
private:
	//Constants
	const float GRAVITY;
	const float MAX_GRAVITY;
	const float JUMP_POWER;
	const float JUMP_CUT_MAGNITUDE;
	const int JUMP_NUMBER;
	const float MAX_SPEED;
	const float MAX_SPEED_AIR;
	const float ACCEL;
	const float ACCEL_AIR;
	const float DECEL;

	//Variables
	float currentAcceleration;
	int remainingJumps;
	bool isAccelerating;

	//GUI
	Label nameLabel;

	//Functions
	void setupAnimation(sf::Vector2u imOffset);

public:
	//Constructors
	Player(std::string path="", 
		sf::Vector2f position = sf::Vector2f(0, 0), 
		sf::Vector2u imgCount = sf::Vector2u(1, 1));

	//Setters
	void setName(const std::string name);

	//Accessors
	const bool isMoving() const;
	const bool isInAir() const;
	const std::string getName() const;

	//Functions
	void checkInputs(std::map<std::string, sf::Keyboard::Key> pressed, 
		std::map<std::string, sf::Keyboard::Key> released,
		std::map<std::string, sf::Keyboard::Key> tapped);
	void manageAcceleration(const float deltaTime);
	void manageDeceleration(const float deltaTime);
	void manageDirectionCut();
	void update(const float deltaTime);
	void move(const float deltaTime);
	void manageAnimations(const float deltaTime);
	std::string selectAnimation();
	void updateSpeedAnimation(std::string name);
	void applyGravity(const float deltaTime);
	void manageSpeedInAir();

	void collideTop();
	void collideBottom();
	void collideLeft();
	void collideRight();

	void updateLabel();

	void drawLabel(sf::RenderWindow& window);
};

#endif // !PLAYER_H