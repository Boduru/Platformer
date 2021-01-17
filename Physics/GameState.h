#ifndef GAMESTATE_H
#define GAMESTATE_H

class State;
class CameraFollower;
class Player;
class Level;

class GameState : public State
{
private:
	//Variables
	CameraFollower camera;
	Level* level;
	Player* player;

	bool drawNameLabels;
	Label* fps;

public:
	//Constructors/Destructors
	GameState();
	GameState(const States& state, const float& width, const float& height);
	virtual ~GameState();

	//Accessors
	Camera& getCamera();

	//Functions
	void configureLabels();
	void configureButtons();
	void configureInputs();
	void configureComboboxes();
	void configureSliders();
	void configureDropboxes();
	void configurePlayer();

	void updateLabels(std::map<std::string, sf::Keyboard::Key> tapped, const float& deltatime);

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

#endif // !GAMESTATE_H