#include "stdafx.h"

//Constructors/Destructors
SettingsState::SettingsState() : SettingsState(States::Settings, 0.f, 0.f)
{

}

SettingsState::SettingsState(const States& state, const float& width, const float& height)
	: State(state, width, height)
{
	this->configure();
}

SettingsState::~SettingsState()
{

}

//Functions
void SettingsState::configureLabels()
{
	Label title(sf::Vector2f(0.f, -260.f), "Settings", FONT_BASIC, 80);
	title.setOrigin();
	this->labels.push_back(title);
}

void SettingsState::configureInputs()
{
	std::ifstream prefs;
	prefs.open(PLAYER_PREFERENCES);

	std::string line;

	//SET FPS
	getline(prefs, line);
	line = line.substr(line.find(':') + 1, -1);

	prefs.close();

	TextInput name_input("NAME", sf::Vector2f(-460.f, -200.f), GUI_PATH + "input.png", GUI_PATH + "bar.png", sf::Vector2f(10, 40), sf::Vector2f(10, 13), "Pseudo");
	name_input.addLetter(line);
	this->inputs.push_back(name_input);
}

void SettingsState::configureButtons()
{
	Button accept("VALIDATE", 420.f, 280.f, GUI_PATH + "discard.png", sf::Vector2u(1, 4));
	Button discard("DISCARD", 520.f, 280.f, GUI_PATH + "discard.png", sf::Vector2u(1, 4));

	this->buttons.push_back(accept);
	this->buttons.push_back(discard);
}

void SettingsState::configureComboboxes()
{
	int index = 0;

	//SET SCREEN SIZE
	std::string line = Utils::getNthLineContent(GAME_PREFERENCES, 2);

	if (line == "medium")
		index = 1;

	else if (line == "large")
		index = 2;

	ComboBox screen_size("SCREEN_SIZE", sf::Vector2f(-460.f, -64.f), sf::Vector2f(-60.f, -64.f), GUI_PATH + "arrow.png", std::vector<std::string> { "small", "medium", "large" });
	screen_size.setCurrentIndex(index);
	this->comboboxes.push_back(screen_size);
}

void SettingsState::configureSliders()
{	
	Slider fps_slider("FPS", sf::Vector2f(-460.f, 64.f), GUI_PATH + "fps_slider.png", GUI_PATH + "pin.png", 30, 120, 5, 90);
	fps_slider.setDefault(std::stoi(Utils::getNthLineContent(GAME_PREFERENCES, 1)));

	Slider music_slider("MUSIC", sf::Vector2f(120.f, -64.f), GUI_PATH + "music_slider.png", GUI_PATH + "pin.png", 0, 100, 1, 50);
	music_slider.setDefault(std::stoi(Utils::getNthLineContent(GAME_PREFERENCES, 3)));

	Slider sound_slider("SOUND", sf::Vector2f(120.f, 64.f), GUI_PATH + "sound_slider.png", GUI_PATH + "pin.png", 0, 100, 1, 50);
	sound_slider.setDefault(std::stoi(Utils::getNthLineContent(GAME_PREFERENCES, 4)));

	this->sliders.push_back(fps_slider);
	this->sliders.push_back(music_slider);
	this->sliders.push_back(sound_slider);
}

void SettingsState::configureDropboxes()
{
}

void SettingsState::savePreferences()
{
	this->saveGamePreferences();
	this->savePlayerPreferences();
}

void SettingsState::saveGamePreferences()
{
	std::ofstream of;
	of.open(GAME_PREFERENCES);

	//FPS
	std::string line;
	auto fps = std::find_if(this->sliders.begin(), this->sliders.end(), [&line](const Slider& obj) {return obj.getName() == "FPS"; });

	of << "fps:" << fps->getNumber() << "\n";

	//SCREEN SIZE
	auto screen = std::find_if(this->comboboxes.begin(), this->comboboxes.end(), [&line](const ComboBox& obj) {return obj.getName() == "SCREEN_SIZE"; });
	of << "screen_size:" << screen->getCurrentLabel() << "\n";

	//MUSIC
	auto music = std::find_if(this->sliders.begin(), this->sliders.end(), [&line](const Slider& obj) {return obj.getName() == "MUSIC"; });
	of << "music:" << music->getNumber() << "\n";

	//SOUND
	auto sound = std::find_if(this->sliders.begin(), this->sliders.end(), [&line](const Slider& obj) {return obj.getName() == "SOUND"; });
	of << "sound:" << sound->getNumber() << "\n";

	of.close();
}

void SettingsState::savePlayerPreferences()
{
	std::ofstream of;
	of.open(PLAYER_PREFERENCES);

	std::string name;
	auto it = std::find_if(this->inputs.begin(), this->inputs.end(), [&name](const TextInput& obj) {return obj.getName() == "NAME"; });

	of << "name:" << it->getContent();

	of.close();
}

void SettingsState::update(std::map<std::string, sf::Keyboard::Key> pressed,
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

	for (int i = 0; i < this->buttons.size(); i++)
	{
		if (this->buttons[i].getButtonName() == "VALIDATE" && this->buttons[i].isButtonClicked())
		{
			//Save preferences
			this->savePreferences();
			break;
		}
	}
}

void SettingsState::updateView(sf::RenderWindow& window, const float& deltatime)
{
	//Update the view

	State::updateView(window, deltatime);
}

void SettingsState::draw(sf::RenderWindow& window)
{
	//Draw the main menu

	State::draw(window);
}