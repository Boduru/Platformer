#include "stdafx.h"

//Constructors/Destructors
LevelChooserState::LevelChooserState() : LevelChooserState(States::LevelChooser, 0.f, 0.f)
{

}

LevelChooserState::LevelChooserState(const States& state, const float& width, const float& height)
	: State(state, width, height),
	startPos(sf::Vector2f(-width / 4.f, -height / 4.f)), span(sf::Vector2f(256.f, 160.f))
{
	this->configure();
}

LevelChooserState::~LevelChooserState()
{

}

void LevelChooserState::configureLabels()
{
	Label title(sf::Vector2f(0.f, -250.f), "Levels", FONT_BASIC, 80);
	title.setOrigin();
	this->labels.push_back(title);
}

//Functions
void LevelChooserState::configureButtons()
{
	int maxRow = (this->camera.getSize().x + this->camera.getLeft() - this->startPos.x) / this->span.x;

	int i = 0;
	int j = 0;
	for (int c = 0; c < 8; c++)
	{
		Button b("LEVEL_0", this->startPos.x + i * this->span.x, this->startPos.y + j * this->span.y, GUI_PATH + "settings_button.png", sf::Vector2u(1, 4));
		this->buttons.push_back(b);

		i++;

		if (i >= maxRow)
		{
			i = 0;
			j++;
		}
	}

	Button right("RIGHT", this->camera.getLeft(), this->camera.getCenter().y, GUI_PATH + "arrow.png", sf::Vector2u(1, 4));
	Button left("LEFT", this->camera.getRight() - 80.f, this->camera.getCenter().y, GUI_PATH + "arrow.png", sf::Vector2u(1, 4), true);
	Button discard("DISCARD", this->camera.getRight() - 80.f, this->camera.getBottom() - 80.f, GUI_PATH + "discard.png", sf::Vector2u(1, 4));

	this->buttons.push_back(right);
	this->buttons.push_back(left);
	this->buttons.push_back(discard);
}

void LevelChooserState::configureInputs()
{
}

void LevelChooserState::configureComboboxes()
{
}

void LevelChooserState::configureSliders()
{
}

void LevelChooserState::configureDropboxes()
{
}

void LevelChooserState::update(std::map<std::string, sf::Keyboard::Key> pressed,
	std::map<std::string, sf::Keyboard::Key> released,
	std::map<std::string, sf::Keyboard::Key> tapped,
	std::map<std::string, sf::Mouse::Button> clicked,
	std::map<std::string, sf::Mouse::Button> uncliked,
	std::map<std::string, sf::Mouse::Button> one_hit_click,
	sf::Vector2i mouse_pos_view,
	sf::Vector2f mouse_pos_window,
	const float deltatime)
{
	//Update the menu

	State::update(pressed, released, tapped, clicked, uncliked, one_hit_click, mouse_pos_view, mouse_pos_window, deltatime);
}

void LevelChooserState::updateView(sf::RenderWindow& window, const float& deltatime)
{
	//Update the view

	State::updateView(window, deltatime);
}

void LevelChooserState::draw(sf::RenderWindow& window)
{
	//Draw the main menu

	State::draw(window);
}