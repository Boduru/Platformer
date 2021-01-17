#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>

class Animator;

#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
private:
	//Static variables
	static unsigned idCounter;

	//Variables
	unsigned id;

	sf::Vector2f initPos;
	sf::FloatRect box;

	//Functions
	void setupTextureSheet(std::string path);
	void setupSprite(sf::Vector2f position);
	void setupAnimation(sf::Vector2u imOffset);

	//Static functions
	static void updateIdCounter();

public:
	//Constructors/Destructors
	Entity(std::string path = "", sf::Vector2f position = sf::Vector2f(0, 0), sf::Vector2u imOffset = sf::Vector2u(1, 1));
	Entity(sf::Texture texture, sf::Vector2f position = sf::Vector2f(0, 0), sf::Vector2u imOffset = sf::Vector2u(1, 1));
	Entity(sf::Vector2f position, sf::Vector2f size);

	virtual ~Entity();

	//Accessors
	const sf::Vector2f getInitPos() const;
	const sf::Vector2f getVelocity() const;
	const sf::Vector2f getPrevPosition() const;

	virtual const sf::Vector2f getCenter() const;
	virtual const sf::Vector2f getTopLeft() const;
	virtual const sf::Vector2f getTopRight() const;
	virtual const sf::Vector2f getBottomLeft() const;
	virtual const sf::Vector2f getBottomRight() const;

	const float getTop() const;
	const float getBottom() const;
	const float getRight() const;
	const float getLeft() const;
	const float getPrevTop() const;
	const float getPrevBottom() const;
	const float getPrevRight() const;
	const float getPrevLeft() const;
	const sf::Vector2f getSize() const;
	const int getDepth() const;
	const int getSide() const;
	const unsigned int getId() const;

	//Mofidiers
	void setVelocity(sf::Vector2f velocity);
	void setPosition(sf::Vector2f position);
	void setTop(const float top);
	void setBottom(const float bottom);
	void setLeft(const float left);
	void setRight(const float right);
	void setSize(sf::Vector2u imOffset);
	void setSize(sf::Vector2f size);
	void setDepth(const int depth);
	void setSide(const int side);

	//Functions
	static const bool isFreeId(const unsigned int id);

	void resize(int factor);

	virtual void updateAnimation(const std::string name, const float deltaTime, const bool flip = false);

	virtual void collideTop();
	virtual void collideBottom();
	virtual void collideLeft();
	virtual void collideRight();

	virtual void move();
	virtual void update(const float deltaTime);

	void draw(sf::RenderWindow& window);

	//Static
	static const bool DepthCompare(Entity* one, Entity* two);

	//Operators
	bool operator==(const Entity* other);

protected:
	//Variables
	unsigned depth;
	int side;

	Animator animator;

	sf::Texture* texture;
	sf::Sprite sprite;
	sf::Vector2f size;
	sf::Vector2f velocity;
	sf::Vector2f prevPosition;
};

#endif