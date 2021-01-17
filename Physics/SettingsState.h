#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

class State;
class Camera;

class SettingsState : public State
{
private:

public:
	//Constructors/Destructors
	SettingsState();
	SettingsState(const States& name, const float& width, const float& height);
	virtual ~SettingsState();

	//Functions
	void configureLabels();
	void configureInputs();
	void configureButtons();
	void configureComboboxes();
	void configureSliders();
	void configureDropboxes();

	void savePreferences();
	void saveGamePreferences();
	void savePlayerPreferences();

	void update(std::map<std::string, sf::Keyboard::Key> pressed,
		std::map<std::string, sf::Keyboard::Key> released,
		std::map<std::string, sf::Keyboard::Key> tapped,
		std::map<std::string, sf::Mouse::Button> clicked,
		std::map<std::string, sf::Mouse::Button> uncliked,
		std::map<std::string, sf::Mouse::Button> one_hit_click,
		sf::Vector2i mouse_pos_view,
		sf::Vector2f mouse_pos_window,
		const float deltatime);
	void updateView(sf::RenderWindow& window, const float& deltatime);
	void draw(sf::RenderWindow& window);
};

#endif // !SETTINGSSTATE_H

