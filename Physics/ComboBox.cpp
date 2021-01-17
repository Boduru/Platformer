#include "stdafx.h"

//Constructors/Destructors
ComboBox::ComboBox(const std::string& name, const sf::Vector2f posStart, const sf::Vector2f posEnd, const std::string pathArrowSheet, const std::vector<std::string> texts)
	: name(name), initPos(posStart), posStart(posStart), posEnd(posEnd), texts(texts), currentIndex(1), label(Label(sf::Vector2f(0, 0), "", FONT_BASIC, 30))
{
	this->setupArrows(posStart, posEnd, pathArrowSheet);
}

ComboBox::~ComboBox()
{
}

void ComboBox::setPosition(const sf::Vector2f& position)
{
	
}

void ComboBox::setCurrentIndex(int index)
{
	if (index >= 0 && index < this->texts.size())
		this->currentIndex = index;
}

const sf::Vector2f ComboBox::getInitPos() const
{
	return this->initPos;
}

const std::string ComboBox::getName() const
{
	return this->name;
}

//Accessors
const std::string ComboBox::getCurrentLabel() const
{
	return this->texts[this->currentIndex];
}

const int& ComboBox::getCurrentIndex() const
{
	return this->currentIndex;
}

//Functions
void ComboBox::setupArrows(const sf::Vector2f posStart, const sf::Vector2f posEnd, const std::string pathArrowSheet)
{
	this->rightArrow = Button("RIGHT_ARROW", posStart.x, posStart.y, pathArrowSheet, sf::Vector2u(1, 4));
	this->leftArrow = Button("LEFT_ARROW", posEnd.x, posEnd.y, pathArrowSheet, sf::Vector2u(1, 4));
}

void ComboBox::update(const float& deltatime, std::map<std::string, sf::Mouse::Button> clicked, std::map<std::string, sf::Mouse::Button> uncliked, sf::Vector2i mouse_pos_view, sf::Vector2f mouse_pos_window)
{
	this->rightArrow.update(deltatime, clicked, uncliked, mouse_pos_view, mouse_pos_window, true);
	this->leftArrow.update(deltatime, clicked, uncliked, mouse_pos_view, mouse_pos_window);

	if (this->leftArrow.isButtonClicked())
		this->currentIndex--;

	else if (this->rightArrow.isButtonClicked())
		this->currentIndex++;

	if (this->currentIndex < 0)
		this->currentIndex = this->texts.size() - 1;

	else if (this->currentIndex > this->texts.size() - 1)
		this->currentIndex = 0;

	this->label.setContent(this->texts[this->currentIndex]);
	this->label.setPosition(sf::Vector2f((this->posStart.x + this->leftArrow.getGlobalBounds().width + this->posEnd.x) / 2.f - this->label.getGlobalBounds().width / 2.f, 
		this->posStart.y + this->label.getGlobalBounds().height / 2.f));
}

void ComboBox::draw(sf::RenderWindow* window)
{
	this->rightArrow.draw(window);
	this->leftArrow.draw(window);
	this->label.draw(window);
}