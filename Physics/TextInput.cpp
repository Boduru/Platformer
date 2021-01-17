#include "stdafx.h"

//Constructors/Destructors
TextInput::TextInput(const std::string& name, const sf::Vector2f& position, const std::string& field_texture, const std::string& bar_texture, const sf::Vector2f& label_offset, const sf::Vector2f& bar_offset, const std::string& help_text)
	: name(name), initPos(position), labelOffset(label_offset), barOffset(bar_offset), helpText(help_text),
	helpLabel(position + label_offset, help_text, FONT_BASIC, 20),
	textLabel(position + label_offset, "", FONT_BASIC, 20),
	field("FIELD", position.x, position.y, field_texture, sf::Vector2u(1, 4)),
	isActive(false), currentTime(0.0f), totalTime(0.6f), maxLenght(20), initTextPos(position + bar_offset)
{
	this->helpLabel.setTextTransparency(150);
	this->helpLabel.setTextStyle(sf::Text::Style::Italic);

	this->barTexture = new sf::Texture();
	this->barTexture->loadFromFile(bar_texture);

	this->barSprite = new sf::Sprite();
	this->barSprite->setTexture(*this->barTexture);

	this->barSprite->setPosition(position + bar_offset);
}

TextInput::~TextInput()
{
	//delete this->barTexture;
	//delete this->barSprite;
}

void TextInput::setPosition(const sf::Vector2f& position)
{

}

const sf::Vector2f TextInput::getInitPos() const
{
	return this->initPos;
}

const std::string TextInput::getName() const
{
	return this->name;
}

//Accessors
const std::string TextInput::getContent() const
{
	return this->content;
}

//Functions
void TextInput::addLetter(const std::string& text)
{
	if (this->content.size() < this->maxLenght)
	{
		this->content += text;
		this->textLabel.setContent(this->content);
		this->barSprite->setPosition(this->initTextPos.x + this->textLabel.getGlobalBounds().width, this->initTextPos.y);
	}
}

void TextInput::removeLetter()
{
	if (this->content.size() > 0)
	{
		this->content = this->content.substr(0, this->content.size() - 1);
		this->textLabel.setContent(this->content);
		this->barSprite->setPosition(this->initTextPos.x + this->textLabel.getGlobalBounds().width, this->initTextPos.y);
	}
}

std::string TextInput::mapToString(std::map<std::string, sf::Keyboard::Key> tapped)
{
	std::vector<std::string> keys;

	for (std::map<std::string, sf::Keyboard::Key>::iterator it = tapped.begin(); it != tapped.end(); ++it)
	{
		if (it->first.size() == 1)
			keys.push_back(it->first);

		else if (it->first == "BACKSPACE")
			return "BACKSPACE";
	}

	return std::accumulate(keys.begin(), keys.end(), std::string{});
}

void TextInput::update(const float& deltatime, std::map<std::string, sf::Keyboard::Key> tapped, std::map<std::string, sf::Mouse::Button> clicked, std::map<std::string, sf::Mouse::Button> uncliked, sf::Vector2i mouse_pos_view, sf::Vector2f mouse_pos_window)
{
	this->field.update(deltatime, clicked, uncliked, mouse_pos_view, mouse_pos_window);

	if (this->content.size() > 0)
		this->helpLabel.setTextTransparency(0);
	else
		this->helpLabel.setTextTransparency(150);

	if (clicked.find("LEFT") != clicked.end() && this->field.isButtonClicked())
		this->isActive = true;

	if (uncliked.find("LEFT") != uncliked.end() && !this->field.hasOverlap(sf::Vector2i(mouse_pos_window)))
		this->isActive = false;

	if (this->isActive)
	{
		this->currentTime += deltatime;

		if (this->currentTime >= this->totalTime)
			this->currentTime = 0.0f;

		std::string letters = this->mapToString(tapped);

		if (letters == "BACKSPACE")
			this->removeLetter();

		else if (letters.size() > 0)
			this->addLetter(letters);
	}
}

void TextInput::draw(sf::RenderWindow* window)
{
	this->field.draw(window);
	this->textLabel.draw(window);

	if (!this->textLabel.getContent().size())
		this->helpLabel.draw(window);

	if (this->isActive && this->currentTime < this->totalTime * 0.5f)
		window->draw(*this->barSprite);
}
