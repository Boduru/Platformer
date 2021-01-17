#include "stdafx.h"

//Constructors/Destructors
GameState::GameState() : GameState(States::Play, 0.f, 0.f)
{
}

GameState::GameState(const States& name, const float& width, const float& height)
	: State(name, width, height), drawNameLabels(false)
{
	this->camera = CameraFollower(sf::Vector2f(0, 0), sf::Vector2f(width, height));
	this->level = new Level(MAP_PATH + "level_1.txt", "Level 1");
	this->player = new Player(TILESETS_IMAGES_PATH + "player_sprite_sheet.png", sf::Vector2f(0, -256), sf::Vector2u(3, 18));
	this->fps = new Label(sf::Vector2f(10.f, 10.f), "", FONT_BASIC, 20);

	this->configurePlayer();
}

GameState::~GameState()
{
	delete this->player;
	delete this->level;
	delete this->fps;
}

Camera& GameState::getCamera()
{
	return this->camera;
}

void GameState::configureLabels()
{
}

void GameState::configureButtons()
{
}

void GameState::configureInputs()
{
}

void GameState::configureComboboxes()
{
}

void GameState::configureSliders()
{
}

void GameState::configureDropboxes()
{
}

void GameState::configurePlayer()
{
	std::ifstream prefs;
	prefs.open(PLAYER_PREFERENCES);

	std::string line;
	getline(prefs, line);

	this->player->setName(line.substr(line.find(':') + 1, -1));

	prefs.close();
}

void GameState::updateLabels(std::map<std::string, sf::Keyboard::Key> tapped, const float& deltatime)
{
	if (tapped["TAB"])
		this->drawNameLabels ^= true;

	std::stringstream ss;
	ss <<  "FPS: " << roundf(1 / deltatime);
	this->fps->setContent(ss.str());
}

//Functions
void GameState::update(std::map<std::string, sf::Keyboard::Key> pressed, 
	std::map<std::string, sf::Keyboard::Key> released, 
	std::map<std::string, sf::Keyboard::Key> tapped, 
	std::map<std::string, sf::Mouse::Button> clicked, 
	std::map<std::string, sf::Mouse::Button> uncliked, 
	std::map<std::string, sf::Mouse::Button> one_hit_click,
	sf::Vector2i mouse_pos_view,
	sf::Vector2f mouse_pos_window,
	const float deltatime)
{
	//Update the game

	State::update(pressed, released, tapped, clicked, uncliked, one_hit_click, mouse_pos_view, mouse_pos_window, deltatime);

	this->player->checkInputs(pressed, released, tapped);
	this->player->update(deltatime);
	this->level->updateLevel(this->camera, *this->player, deltatime);
	this->updateLabels(tapped, deltatime);
}

void GameState::updateView(sf::RenderWindow& window, const float& deltatime)
{
	//Update the view

	this->camera.update(window, *this->player, deltatime, true);
}

void GameState::draw(sf::RenderWindow& window)
{
	//Draw the game

	State::draw(window);

	this->level->drawLevel(window, this->camera);
	this->player->draw(window);

	if (this->drawNameLabels)
	{
		this->player->drawLabel(window);
		this->fps->setPosition(this->camera.getTopLeft() + this->fps->getInitPos());
		this->fps->draw(&window);
	}
}