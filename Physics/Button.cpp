#include "stdafx.h"

//Constructros/Destructors
Button::Button()
	: texture(nullptr), sprite(nullptr), size(sf::Vector2f(0, 0)), animator(Animator()),
	isClicked(false), isHover(false), isReleased(false), name(""), currentTime(0.0f), totalTime(0.5f)
{
}

Button::Button(const std::string name, const float x, const float y, const std::string path, const sf::Vector2u imOffset, const bool& flip)
	: isClicked(false), isHover(false), isReleased(false), name(name), currentTime(0.0f), totalTime(0.2f), initPos(sf::Vector2f(x, y))
{
	this->texture = new sf::Texture();
	this->texture->loadFromFile(path);

	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*this->texture);
	this->sprite->setPosition(x, y);

	this->size.x = this->sprite->getTextureRect().width / imOffset.x;
	this->size.y = this->sprite->getTextureRect().height / imOffset.y;

	//if (flip)
		//this->sprite->setTextureRect(sf::IntRect(0, 0, -this->sprite->getTextureRect().width, this->sprite->getTextureRect().height));

	this->animator = Animator(this->texture, this->sprite, imOffset);
	this->autoconfigure();
}

Button::~Button()
{
	//delete this->sprite;
	//delete this->texture;
}

//Setters
void Button::setPosition(sf::Vector2f position)
{
	this->sprite->setPosition(position);
}

void Button::setScale(const float& factor)
{
	this->sprite->setScale(factor, factor);
}

const sf::Vector2f Button::getInitPos() const
{
	return this->initPos;
}

//Accessors
const sf::FloatRect Button::getGlobalBounds() const
{
	return this->sprite->getGlobalBounds();
}

const std::string Button::getButtonName() const
{
	return this->name;
}

const bool Button::isButtonClicked() const
{
	return this->isClicked;
}

const bool Button::isButtonHover() const
{
	return this->isHover;
}

const bool Button::isButtonReleased() const
{
	return this->isReleased;
}

void Button::autoconfigure()
{
	this->configureAnimation("IDLE", 0, 0, 0, 0, 0.3f);
	this->configureAnimation("RELEASE", 0, 0, 1, 0, 0.3f);
	this->configureAnimation("HOVER", 0, 0, 2, 0, 0.3f);
	this->configureAnimation("CLICK", 0, 0, 3, 0, 0.3f);
}

void Button::configureAnimation(std::string name, unsigned start_x, unsigned end_x, unsigned start_y, unsigned end_y, float switch_time)
{
	//IDLE, HOVER, CLICK, RELEASE
	this->animator.addAnimation(name, start_x, end_x, start_y, end_y, switch_time);
}

//Functions
bool Button::hasOverlap(sf::Vector2i position)
{
	return position.x > this->sprite->getPosition().x && position.x < this->sprite->getPosition().x + this->size.x && position.y > this->sprite->getPosition().y && position.y < this->sprite->getPosition().y + this->size.y;
}

void Button::update(const float& deltatime, std::map<std::string, sf::Mouse::Button> clicked, std::map<std::string, sf::Mouse::Button> uncliked, sf::Vector2i mouse_pos_view, sf::Vector2f mouse_pos_window, const bool& flip)
{
	this->isClicked = false;
	this->isHover = false;
	this->isReleased = false;

	if (uncliked.find("LEFT") != uncliked.end() && this->hasOverlap(sf::Vector2i(mouse_pos_window)))
	{
		//Released
		this->animator.play("RELEASE", deltatime, flip);
		this->isReleased = true;
	}

	if (clicked.find("LEFT") != clicked.end() && this->hasOverlap(sf::Vector2i(mouse_pos_window)))
	{
		//Clicked
		this->animator.play("CLICK", deltatime, flip);

		if (this->currentTime >= this->totalTime)
		{
			this->isClicked = true;
			this->currentTime = 0.0f;
		}
	}

	else if (clicked.find("LEFT") == clicked.end() && this->hasOverlap(sf::Vector2i(mouse_pos_window)))
	{
		//Hover
		this->animator.play("HOVER", deltatime, flip);
		this->isHover = true;
	}

	else
		//Idle
		this->animator.play("IDLE", deltatime, flip);

	if (this->currentTime > this->totalTime)
		this->currentTime = this->totalTime;
	else
		this->currentTime += deltatime;
}

void Button::draw(sf::RenderWindow* window)
{
	if (this->texture != nullptr)
		window->draw(*this->sprite);
}

//Operators
void Button::operator=(const Button& button)
{
	this->name = button.name;
	this->size = button.size;
	this->totalTime = button.totalTime;
	this->currentTime = button.currentTime;
	this->isClicked = button.isClicked;
	this->isHover = button.isHover;
	this->isReleased = button.isReleased;

	delete this->texture;
	delete this->sprite;

	this->texture = new sf::Texture(*button.texture);
	this->sprite = new sf::Sprite(*button.sprite);

	this->animator = Animator(this->texture, this->sprite, sf::Vector2u(1, 4));
	this->autoconfigure();
}