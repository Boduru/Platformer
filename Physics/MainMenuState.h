#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

class MainMenuState : public State
{
private:

public:
	//Constructors/Destructors
	MainMenuState();
	MainMenuState(const States& name, const float& width, const float& height);
	virtual ~MainMenuState();

	//Functions
	void configureLabels();
	void configureButtons();
	void configureInputs();
	void configureComboboxes();
	void configureSliders();
	void configureDropboxes();

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

#endif // ! MAINMENUSTATE_H