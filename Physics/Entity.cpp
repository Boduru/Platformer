#include "stdafx.h"

unsigned Entity::idCounter = 1;

//___________Constructors/Destrutors___________
Entity::Entity(std::string path, sf::Vector2f position, sf::Vector2u imOffset)
	: box(sf::FloatRect(position, sf::Vector2f(64, 64))), prevPosition(position), initPos(position), side(1), depth(1), velocity(sf::Vector2f(0, 0)), id(idCounter)
{
	this->setupTextureSheet(path);
	this->setupSprite(position);
	this->setSize(imOffset);
	this->setupAnimation(imOffset);

	Entity::updateIdCounter();
}

Entity::Entity(sf::Texture texture, sf::Vector2f position, sf::Vector2u imOffset)
	: prevPosition(position), depth(1), velocity(sf::Vector2f(0, 0)), id(idCounter)
{
	this->texture = new sf::Texture(texture);

	this->setupSprite(position);
	this->setSize(imOffset);
	this->setupAnimation(imOffset);

	Entity::updateIdCounter();
}

Entity::Entity(sf::Vector2f position, sf::Vector2f size)
	: Entity("", position, sf::Vector2u(1, 1))
{
	/*Initialization for Elements that don't have a Texture 
	but have a position and size*/

	this->texture = nullptr;

	this->setSize(size);

	Entity::updateIdCounter();
}

Entity::~Entity()
{
	delete this->texture;
}

//___________Initialization___________
void Entity::setupTextureSheet(std::string path)
{
	this->texture = new sf::Texture();

	/*If the texture doesn'it exist or isn't reachable make it nullptr,
	otherwise load it from the file*/

	if (std::ifstream(path).good())
		this->texture->loadFromFile(path);
	else
		this->texture = nullptr;
}

void Entity::setupSprite(sf::Vector2f position)
{
	if (this->texture != nullptr)
	{
		this->sprite.setTexture(*this->texture);
		this->setPosition(position);
	}
}

void Entity::setupAnimation(sf::Vector2u imOffset)
{
	if (this->texture != nullptr)
	{
		this->animator = Animator(this->texture, &this->sprite, imOffset);
		this->animator.addAnimation("Main", 0, 1, 0, 0, 0.3f);
	}
}

void Entity::updateIdCounter()
{
	Entity::idCounter++;
}

//___________Accessors___________
const int Entity::getDepth() const
{
	return this->depth;
}

const int Entity::getSide() const
{
	return this->side;
}

const unsigned int Entity::getId() const
{
	return this->id;
}

const sf::Vector2f Entity::getInitPos() const
{
	return this->initPos;
}

const sf::Vector2f Entity::getVelocity() const
{
	return this->velocity;
}

const sf::Vector2f Entity::getPrevPosition() const
{
	return this->prevPosition;
}

const sf::Vector2f Entity::getCenter() const
{
	sf::Vector2f pos = this->sprite.getPosition();
	return sf::Vector2f(pos.x + this->size.x / 2, pos.y + this->size.y / 2);
}

const sf::Vector2f Entity::getTopLeft() const
{
	return this->sprite.getPosition();
}

const sf::Vector2f Entity::getTopRight() const
{
	sf::Vector2f pos = this->sprite.getPosition();
	return sf::Vector2f(pos.x + this->size.x, pos.y);
}

const sf::Vector2f Entity::getBottomLeft() const
{
	sf::Vector2f pos = this->sprite.getPosition();
	return sf::Vector2f(pos.x, pos.y + this->size.y);
}

const sf::Vector2f Entity::getBottomRight() const
{
	sf::Vector2f pos = this->sprite.getPosition();
	return sf::Vector2f(pos.x + this->size.x, pos.y + this->size.y);
}

const float Entity::getTop() const
{
	return this->sprite.getPosition().y;
}

const float Entity::getBottom() const
{
	return this->sprite.getPosition().y + this->size.y;
}

const float Entity::getRight() const
{
	return this->sprite.getPosition().x + this->size.x;
}

const float Entity::getLeft() const
{
	return this->sprite.getPosition().x;
}

const float Entity::getPrevTop() const
{
	return this->prevPosition.y;
}

const float Entity::getPrevBottom() const
{
	return this->prevPosition.y + this->size.y;
}

const float Entity::getPrevRight() const
{
	return this->prevPosition.x + this->size.x;
}

const float Entity::getPrevLeft() const
{
	return this->prevPosition.x;
}

const sf::Vector2f Entity::getSize() const
{
	return this->size;
}

//___________Modifiers___________
void Entity::setVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}

void Entity::setDepth(const int depth)
{
	this->depth = depth;
}

void Entity::setSide(const int side)
{
	this->side = side;
}

void Entity::setPosition(sf::Vector2f position)
{
	this->sprite.setPosition(position);
}

void Entity::setTop(const float top)
{
	this->sprite.setPosition(this->getLeft(), top);
}

void Entity::setBottom(const float bottom)
{
	this->sprite.setPosition(this->getLeft(), bottom - this->getSize().y);
}

void Entity::setLeft(const float left)
{
	this->sprite.setPosition(left, this->getTop());
}

void Entity::setRight(const float right)
{
	this->sprite.setPosition(right - this->getSize().x, this->getTop());
}

void Entity::setSize(sf::Vector2u imOffset)
{
	/*Set size in function of the animation tiles*/

	sf::FloatRect gb = this->sprite.getGlobalBounds();
	this->size = sf::Vector2f(gb.width / imOffset.x, gb.height / imOffset.y);
}

void Entity::setSize(sf::Vector2f size)
{
	/*Set size*/

	this->size = size;
	//this->box.width = size.x / this->box.width;
}

//___________Functions___________
void Entity::update(const float deltaTime)
{
	//Save the prev position
	this->prevPosition = this->getTopLeft();

	//Move
	this->move();

	//Handle the animations
	this->updateAnimation("Main", deltaTime, false);
}

const bool Entity::isFreeId(const unsigned int id)
{
	return id > Entity::idCounter;
}

void Entity::resize(int factor)
{
	if (this->texture != nullptr)
	{
		this->sprite.scale(sf::Vector2f(factor, factor));
		this->sprite.setPosition((this->getLeft() + 1) * factor, (this->getTop() + 1) * factor);
		this->setSize(this->animator.getImageOffsets());
	}
	else
	{
		this->setSize(sf::Vector2f(this->size.x * factor, this->size.y * factor));
	}
}

//___________Collision responses___________
void Entity::collideTop()
{
}

void Entity::collideBottom()
{
}

void Entity::collideLeft()
{
}

void Entity::collideRight()
{
}

//___________Animations___________
void Entity::updateAnimation(const std::string name, const float deltaTime, const bool flip)
{
	if (this->texture != nullptr)
		this->animator.play(name, deltaTime, flip);
}

//___________Update/Draw___________
void Entity::draw(sf::RenderWindow& window)
{
	if (this->texture != nullptr)
		window.draw(this->sprite);
}

void Entity::move()
{
	this->sprite.setPosition(this->sprite.getPosition() + this->velocity);

	this->box.left = this->sprite.getPosition().x;
	this->box.top = this->sprite.getPosition().y;
}

//___________Comparison___________
const bool Entity::DepthCompare(Entity* one, Entity* two)
{
	return one->getDepth() < two->getDepth();
}

//___________Operators___________
bool Entity::operator==(const Entity* other)
{
	return this->getId() == other->getId();
}