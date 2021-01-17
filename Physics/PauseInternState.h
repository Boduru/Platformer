#ifndef PAUSEINTERNSTATE_H
#define PAUSEINTERNSTATE_H

class Entity;

class PauseInternState : public State
{
private:
	Entity* background;

public:
	//Constructors/Destructors
	PauseInternState();
	PauseInternState(const States& name, const float& width, const float& height);
	virtual ~PauseInternState();

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
		sf::Vector2f camera_pos,
		const float deltatime);
	void updateView(sf::RenderWindow& window, const float& deltatime);
	void draw(sf::RenderWindow& window);
};

#endif // !PAUSEINTERNSTATE_H