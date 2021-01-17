#include "stdafx.h"

//Constructors/Destructors
Slider::Slider(const std::string& name, const sf::Vector2f& position, const std::string& path_slider, const std::string& path_pin, const float& start, const float& stop, const float& step, const float& default_value)
	: name(name), initPos(position), position(position), start(start), stop(stop), step(step), percentage(0.5f), label(Label(sf::Vector2f(0, 0), "", FONT_BASIC, 20))
{
	this->textureSlider = new sf::Texture();
	this->textureSlider->loadFromFile(path_slider);

	this->texturePin = new sf::Texture();
	this->texturePin->loadFromFile(path_pin);

	this->baseSprite = new sf::Sprite();
	this->topSprite = new sf::Sprite();
	this->pinSprite = new sf::Sprite();

	this->baseSprite->setTexture(*this->textureSlider);
	this->topSprite->setTexture(*this->textureSlider);
	this->pinSprite->setTexture(*this->texturePin);

	this->baseSprite->setTextureRect(sf::IntRect(this->textureSlider->getSize().x / 2.f, 0, this->textureSlider->getSize().x / 2.f, this->textureSlider->getSize().y / 2.f));
	this->topSprite->setTextureRect(sf::IntRect(0, this->textureSlider->getSize().y / 2.f, this->textureSlider->getSize().x / 2.f, this->textureSlider->getSize().y / 2.f));

	this->baseSprite->setPosition(position);
	this->topSprite->setPosition(position);

	this->pinSprite->setOrigin(0.5f * this->texturePin->getSize().x, this->texturePin->getSize().y * 0.5f);

	this->setDefault(default_value);
}

Slider::~Slider()
{
	/*delete this->textureSlider;
	delete this->texturePin;

	delete this->baseSprite;
	delete this->topSprite;
	delete this->pinSprite;*/
}

void Slider::setPosition(const sf::Vector2f& position)
{
}

const sf::Vector2f Slider::getInitPos() const
{
	return this->initPos;
}

const std::string Slider::getName() const
{
	return this->name;
}

//Accessors
const float Slider::getNumber() const
{
	return roundf((this->start + this->percentage * (this->stop - this->start)) / this->step) * this->step;
}

bool Slider::hasOverlap(sf::Vector2i position)
{
	return position.x > this->topSprite->getPosition().x && position.x < this->topSprite->getPosition().x + this->textureSlider->getSize().x &&
		position.y > this->baseSprite->getPosition().y && position.y < this->baseSprite->getPosition().y + this->textureSlider->getSize().y / 2.f;
}

//Functions
void Slider::setPercentage(const float& percentage)
{
	if (percentage >= 0.0f && percentage <= 1.f)
	{
		int x = percentage * this->textureSlider->getSize().x;

		this->topSprite->setTextureRect(sf::IntRect(0, this->textureSlider->getSize().y / 2.f, x, this->textureSlider->getSize().y / 2.f));
		this->baseSprite->setTextureRect(sf::IntRect(x, 0, this->textureSlider->getSize().x - x, this->textureSlider->getSize().y / 2.f));

		this->baseSprite->setPosition(this->textureSlider->getSize().x * percentage + this->position.x - 1, position.y);
		this->pinSprite->setPosition(this->textureSlider->getSize().x * percentage + this->position.x - 1, position.y);
		this->label.setPosition(sf::Vector2f(this->textureSlider->getSize().x * percentage + this->position.x - 1, position.y - this->texturePin->getSize().y));
	}
}

void Slider::setDefault(const float& value)
{
	if (value <= this->stop && value >= this->start)
	{
		this->percentage = (value - this->start) / (this->stop - this->start);
		this->setPercentage(this->percentage);
	}
}

void Slider::update(const float& deltatime, std::map<std::string, sf::Mouse::Button> clicked, std::map<std::string, sf::Mouse::Button> uncliked, sf::Vector2i mouse_pos_view, sf::Vector2f mouse_pos_window)
{
	if (this->hasOverlap(sf::Vector2i(mouse_pos_window)))
		this->pinSprite->setScale(1.5f, 1.5f);
	else
		this->pinSprite->setScale(1.f, 1.f);

	if (clicked.find("LEFT") != clicked.end() && this->hasOverlap(sf::Vector2i(mouse_pos_window)))
	{
		this->percentage = (mouse_pos_window.x - this->position.x) / this->textureSlider->getSize().x;
		this->setPercentage(this->percentage);
	}

	std::stringstream ss;
	ss << this->getNumber();
	this->label.setContent(ss.str());
}

void Slider::draw(sf::RenderWindow* window)
{
	this->label.setOrigin();

	window->draw(*this->baseSprite);
	window->draw(*this->topSprite);
	window->draw(*this->pinSprite);
	this->label.draw(window);
}