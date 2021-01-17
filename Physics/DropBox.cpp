#include "stdafx.h"

//Constructors/Destructors
DropBox::DropBox(const sf::Vector2f position, const std::vector<Button> listbox)
	: initPos(position), position(position), listbox(listbox), isSpan(false)
{
	this->init();
}

DropBox::~DropBox()
{
}

void DropBox::setPosition(const sf::Vector2f& position)
{
}

const sf::Vector2f DropBox::getInitPos() const
{
	return this->initPos;
}

//Accessors
const std::vector<Button>& DropBox::getListbox() const
{
	return this->listbox;
}

const Button& DropBox::getSelectedItem() const
{
	return this->selectedItem;
}

//Functions
void DropBox::init()
{
	if (this->listbox.size() > 0)
		this->selectedItem = this->listbox[0];
	else
		this->selectedItem = Button();

	this->selectedItem.setPosition(this->position);
}

void DropBox::update(const float& deltatime, std::map<std::string, sf::Mouse::Button> clicked, std::map<std::string, sf::Mouse::Button> uncliked, sf::Vector2i mouse_pos_view, sf::Vector2f mouse_pos_window)
{
	if (!this->isSpan)
	{
		this->selectedItem.update(deltatime, clicked, uncliked, mouse_pos_view, mouse_pos_window);

		if (this->selectedItem.isButtonClicked())
		{
			this->isSpan = true;
		}
	}

	if (this->isSpan)
	{
		for (int i = 0; i < this->listbox.size(); i++)
		{
			this->listbox[i].update(deltatime, clicked, uncliked, mouse_pos_view, mouse_pos_window);

			if (this->listbox[i].isButtonClicked())
			{
				this->isSpan = false;
			}
			else if (this->listbox[i].isButtonHover())
			{
				//this->listbox[i].setScale(2.f);
			}
		}
	}
}

void DropBox::draw(sf::RenderWindow* window)
{
	this->selectedItem.setPosition(this->position);
	this->selectedItem.draw(window);

	if (this->isSpan)
	{
		for (int i = 0; i < this->listbox.size(); i++)
		{
			this->listbox[i].setPosition(sf::Vector2f(this->position.x, this->position.y + (i + 1) * this->selectedItem.getGlobalBounds().height));
			this->listbox[i].draw(window);
		}
	}
}