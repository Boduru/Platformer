#include "stdafx.h"

//Constructors/Destructors
MainMenuState::MainMenuState() : MainMenuState(States::Main, 0.f, 0.f)
{

}

MainMenuState::MainMenuState(const States& state, const float& width, const float& height)
	: State(state, width, height)
{
	this->configure();
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::configureLabels()
{
	Label title(sf::Vector2f(0.f, -250.f), "Silent Hill", FONT_BASIC, 80);
	title.setOrigin();
	this->labels.push_back(title);
}

//Functions
void MainMenuState::configureButtons()
{
	Button play("PLAY", -250.f, -50.f, GUI_PATH + "start.png", sf::Vector2u(1, 4));
	Button quit("QUIT", 150.f, 180.f, GUI_PATH + "quit_button.png", sf::Vector2u(1, 4));
	Button levels("LEVEL_CHOOSER", -270.f, 180.f, GUI_PATH + "levels_button.png", sf::Vector2u(1, 4));
	Button settings("SETTINGS", 10.f, 180.f, GUI_PATH + "settings_button.png", sf::Vector2u(1, 4));
	Button multiplayer("MULTIPLAYER", -130.f, 180.f, GUI_PATH + "multiplayer_button.png", sf::Vector2u(1, 4));

	this->buttons.push_back(play);
	this->buttons.push_back(levels);
	this->buttons.push_back(settings);
	this->buttons.push_back(multiplayer);
	this->buttons.push_back(quit);
}

void MainMenuState::configureInputs()
{
}

void MainMenuState::configureComboboxes()
{
}

void MainMenuState::configureSliders()
{
}

void MainMenuState::configureDropboxes()
{
	/*Button play("PLAY", 0.f, 100.f, "..//Resources//Images//GUI//start.png", sf::Vector2u(1, 4));
	Button playp("y", 0.f, 100.f, "..//Resources//Images//GUI//start.png", sf::Vector2u(1, 4));
	Button playm("h", 0.f, 100.f, "..//Resources//Images//GUI//start.png", sf::Vector2u(1, 4));

	DropBox dropbox(sf::Vector2f(50.f, 50.f), std::vector<Button> { play, playp, playm });
	this->dropboxes.push_back(dropbox);*/
}

void MainMenuState::update(std::map<std::string, sf::Keyboard::Key> pressed,
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

void MainMenuState::updateView(sf::RenderWindow& window, const float& deltatime)
{
	//Update the view
	
	State::updateView(window, deltatime);
}

void MainMenuState::draw(sf::RenderWindow& window)
{
	//Draw the main menu

	State::draw(window);
}