#ifndef LEVELCHOOSERSTATE_H
#define LEVELCHOOSERSTATE_H

class State;
class Camera;

class LevelChooserState : public State
{
private:
	sf::Vector2f startPos;
	sf::Vector2f span;

public:
	//Constructors/Destructors
	LevelChooserState();
	LevelChooserState(const States& name, const float& width, const float& height);
	virtual ~LevelChooserState();

	//Functions
	void configureLabels();
	void configureInputs();
	void configureButtons();
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

#endif // !LEVELCHOOSERSTATE_H