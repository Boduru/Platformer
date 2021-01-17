#include "stdafx.h"

//___________Constructors/Destructors___________
Player::Player(std::string path, sf::Vector2f position, sf::Vector2u imOffset)
	: Entity(path, position, imOffset),
	ACCEL(512.f), DECEL(1024.f), ACCEL_AIR(320.f), MAX_SPEED(512.f), MAX_SPEED_AIR(384.f), MAX_GRAVITY(1024.f),
	GRAVITY(1024.f), JUMP_POWER(512.f), JUMP_CUT_MAGNITUDE(128.f), JUMP_NUMBER(2),
	isAccelerating(false), currentAcceleration(ACCEL_AIR), remainingJumps(JUMP_NUMBER),
	nameLabel(Label(position, "", FONT_BASIC, 10))
{
	this->nameLabel.setOrigin();
	this->setupAnimation(imOffset);
}

void Player::setName(const std::string name)
{
	this->nameLabel.setContent(name);
}

//___________Functions___________
void Player::update(const float deltaTime)
{
	//Save the previous topleft sprite corner position
	this->prevPosition = this->getTopLeft();

	//Handle the animations
	this->manageAnimations(deltaTime);

	//Apply physics and update sprite
	this->manageDeceleration(deltaTime);
	this->manageAcceleration(deltaTime);
	this->manageSpeedInAir();
	this->applyGravity(deltaTime);
	this->manageDirectionCut();
	this->updateLabel();
	this->move(deltaTime);
}

//___________Animations___________
void Player::setupAnimation(sf::Vector2u imOffset)
{
	if (this->texture != nullptr)
	{
		this->animator = Animator(this->texture, &this->sprite, imOffset);
		//Setup(match) the animation rows with names
		this->animator.addAnimation("IDLE", 0, 2, 0, 0, 0.3f);
		this->animator.addAnimation("JUMP_ASC", 2, 2, 2, 2, 0.3f);
		this->animator.addAnimation("JUMP_DESC", 0, 0, 2, 2, 0.3f);
		this->animator.addAnimation("RUN", 0, 2, 1, 1, 0.3f);
	}
}

std::string Player::selectAnimation()
{
	/*Select the row/animation which will be played this frame,
	depending on the Player's state (running/jumping/idle)*/

	std::string state = "IDLE";

	if (this->isMoving())
		state = "RUN";

	if (this->isInAir())
	{
		if (this->velocity.y < 0)
			state = "JUMP_ASC";
		else
			state = "JUMP_DESC";
	} 

	return state;
}

void Player::updateSpeedAnimation(std::string name)
{
	//Adjust the speed of the animation played depending on the speed of the Player following simple linear equation

	this->animator.setSwitchTime(name, static_cast<float>(-0.0005 * abs(this->velocity.x) + 0.4));
}

void Player::manageAnimations(const float deltaTime)
{
	std::string name = this->selectAnimation();
	bool flip = (this->side > 0) ? true : false;

	this->updateAnimation(name, deltaTime, flip);
	this->updateSpeedAnimation(name);
}

//___________Speed and moving system___________
void Player::manageAcceleration(const float deltaTime)
{
	if (this->isAccelerating)
	{
		this->velocity.x += this->currentAcceleration *deltaTime* this->side;

		if (abs(this->velocity.x) >= this->MAX_SPEED)
			this->velocity.x = this->MAX_SPEED * this->side;
	}
}

void Player::manageDeceleration(const float deltaTime)
{
	if (!this->isAccelerating)
	{
		this->velocity.x += this->DECEL * deltaTime * this->side * -1;

		if ((this->side < 0 && this->velocity.x >= 0) || (this->side > 0 && this->velocity.x <= 0))
			this->velocity.x = 0;
	}
}

void Player::manageDirectionCut()
{
	if ((this->velocity.x < 0 && this->side > 0) || (this->velocity.x > 0 && this->side < 0))
		this->velocity.x = 0;
}

void Player::applyGravity(const float deltaTime) {
	this->velocity.y += this->GRAVITY * deltaTime;

	if (this->velocity.y >= this->MAX_GRAVITY)
		this->velocity.y = this->MAX_GRAVITY;
}

void Player::manageSpeedInAir()
{
	if (this->isInAir())
	{
		this->currentAcceleration = this->ACCEL_AIR;

		if (abs(this->velocity.x) >= this->MAX_SPEED_AIR)
			this->velocity.x = this->MAX_SPEED_AIR * this->side;
	}
	else
		this->currentAcceleration = this->ACCEL;
}

void Player::move(const float deltaTime)
{
	//Move the sprite player

	this->sprite.move(this->velocity * deltaTime);
}

//Collisions
void Player::collideTop()
{
	this->velocity.y = 0;
	this->remainingJumps = this->JUMP_NUMBER;
}

void Player::collideBottom()
{
	this->velocity.y = 0.1;
}

void Player::collideLeft()
{
	this->velocity.x = 0;
}

void Player::collideRight()
{
	this->velocity.x = 0;
}

void Player::updateLabel()
{
	this->nameLabel.setPosition(sf::Vector2f(this->getCenter().x - this->nameLabel.getGlobalBounds().width / 2.f, this->getTop()));
}

void Player::drawLabel(sf::RenderWindow& window)
{
	this->nameLabel.draw(&window);
}

//____________Inputs___________
void Player::checkInputs(std::map<std::string, sf::Keyboard::Key> pressed,
	std::map<std::string, sf::Keyboard::Key> released, 
	std::map<std::string, sf::Keyboard::Key> tapped)
{
	this->isAccelerating = false;

	//JUMP
	if (tapped["UP"])
	{
		if ((this->isInAir() && this->remainingJumps > 0) || (!this->isInAir()))
		{
			this->velocity.y = -this->JUMP_POWER;
			this->remainingJumps--;
		}
	}

	//CUT the JUMP
	if (released["UP"] && this->velocity.y < -this->JUMP_CUT_MAGNITUDE)
		this->velocity.y = -this->JUMP_CUT_MAGNITUDE;

	//GO LEFT
	if (pressed["LEFT"]) {
		this->isAccelerating = true;
		this->side = -1;
	}

	//GO RIGHT
	if (pressed["RIGHT"]) {
		this->isAccelerating = true;
		this->side = 1;
	}
}

//___________Accessors___________
const bool Player::isMoving() const
{
	return this->velocity.x != 0;
}

const bool Player::isInAir() const
{
	return this->velocity.y != 0;
}

const std::string Player::getName() const
{
	return this->nameLabel.getContent();
}

//___________Modifiers___________