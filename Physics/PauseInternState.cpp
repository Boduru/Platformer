#include "stdafx.h"

//Constructors/Destructors
PauseInternState::PauseInternState() : PauseInternState(States::Main, 0.f, 0.f)
{

}

PauseInternState::PauseInternState(const States& state, const float& width, const float& height)
	: State(state, width, height)
{
	this->background = new Entity(GUI_PATH + "menu.png", sf::Vector2f(-350.f, -100.f), sf::Vector2u(1, 1));

	this->configure();
}

PauseInternState::~PauseInternState()
{
	delete this->background;
}

void PauseInternState::configureLabels()
{
	Label title(sf::Vector2f(0.f, -250.f), "Pause", FONT_BASIC, 80);
	title.setOrigin();
	this->labels.push_back(title);
}

//Functions
void PauseInternState::configureButtons()
{
	Button play("RESUME", -270.f, 80.f, GUI_PATH + "play_button.png", sf::Vector2u(1, 4));
	Button quit("RETURN", 150.f, 80.f, GUI_PATH + "quit_button.png", sf::Vector2u(1, 4));
	Button levels("LEVEL_CHOOSER", -130.f, 80.f, GUI_PATH + "levels_button.png", sf::Vector2u(1, 4));
	Button settings("SETTINGS", 10.f, 80.f, GUI_PATH + "settings_button.png", sf::Vector2u(1, 4));

	this->buttons.push_back(play);
	this->buttons.push_back(levels);
	this->buttons.push_back(settings);
	this->buttons.push_back(quit);
}

void PauseInternState::configureInputs()
{
}

void PauseInternState::configureComboboxes()
{
}

void PauseInternState::configureSliders()
{
}

void PauseInternState::configureDropboxes()
{
}

void PauseInternState::update(std::map<std::string, sf::Keyboard::Key> pressed,
	std::map<std::string, sf::Keyboard::Key> released,
	std::map<std::string, sf::Keyboard::Key> tapped,
	std::map<std::string, sf::Mouse::Button> clicked,
	std::map<std::string, sf::Mouse::Button> uncliked,
	std::map<std::string, sf::Mouse::Button> one_hit_click,
	sf::Vector2i mouse_pos_view,
	sf::Vector2f mouse_pos_window,
	sf::Vector2f camera_pos,
	const float deltatime)
{
	//Update the menu

	for (int i = 0; i < this->labels.size(); i++)
		this->labels[i].setPosition(this->labels[i].getInitPos() + camera_pos);

	for (int i = 0; i < this->buttons.size(); i++)
		this->buttons[i].setPosition(this->buttons[i].getInitPos() + camera_pos);

	for (int i = 0; i < this->comboboxes.size(); i++)
		this->comboboxes[i].setPosition(this->comboboxes[i].getInitPos() + camera_pos);

	for (int i = 0; i < this->inputs.size(); i++)
		this->inputs[i].setPosition(this->inputs[i].getInitPos() + camera_pos);

	for (int i = 0; i < this->sliders.size(); i++)
		this->sliders[i].setPosition(this->sliders[i].getInitPos() + camera_pos);

	for (int i = 0; i < this->dropboxes.size(); i++)
		this->dropboxes[i].setPosition(this->dropboxes[i].getInitPos() + camera_pos);

	State::update(pressed, released, tapped, clicked, uncliked, one_hit_click, mouse_pos_view, mouse_pos_window, deltatime);

	this->background->update(deltatime);
	this->background->setPosition(this->background->getInitPos() + camera_pos);
}

void PauseInternState::updateView(sf::RenderWindow& window, const float& deltatime)
{
	//Update the view

	State::updateView(window, deltatime);
}

void PauseInternState::draw(sf::RenderWindow& window)
{
	//Draw the main menu

	this->background->draw(window);

	State::draw(window);
}