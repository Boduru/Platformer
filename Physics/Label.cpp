#include "stdafx.h"

//Constructors/Destructors
Label::Label(const sf::Vector2f& position, const std::string& content, const std::string& font, const int& characterSize)
	: initPos(position)
{
	this->font = new sf::Font();
	this->font->loadFromFile(font);

	this->text = new sf::Text();
	this->text->setFont(*this->font);
	this->text->setCharacterSize(characterSize);

	this->setContent(content);

	this->text->setPosition(position);
}

Label::~Label()
{
	//delete this->text;
	//delete this->font;
}

//Setters
void Label::setOrigin()
{
	this->text->setOrigin(this->text->getGlobalBounds().width * 0.5f, this->text->getGlobalBounds().height * 0.5f);
}

void Label::setPosition(const sf::Vector2f& position)
{
	this->text->setPosition(position);
}

void Label::setContent(const std::string& content)
{
	this->content = content;
	this->text->setString(content);
}

void Label::setCharacterSize(const int& size)
{
	this->characterSize = size;
}

void Label::setTextTransparency(const int& amount)
{
	if (amount <= 255 && amount >= 0)
	{
		sf::Color color(this->text->getFillColor());
		color.a = amount;
		this->text->setFillColor(color);
	}
}

void Label::setTextStyle(const sf::Text::Style& style)
{
	this->text->setStyle(style);
}

//Getters
const sf::FloatRect Label::getGlobalBounds() const
{
	return this->text->getGlobalBounds();
}

const sf::Vector2f Label::getPosition() const
{
	return this->text->getPosition();
}

const sf::Vector2f Label::getInitPos() const
{
	return this->initPos;
}

const std::string Label::getContent() const
{
	return this->content;
}

const int Label::getCharacterSize() const
{
	return this->characterSize;
}

const sf::Color Label::getTextColor() const
{
	return this->text->getFillColor();
}

//Functions
void Label::draw(sf::RenderWindow* window)
{
	window->draw(*this->text);
}