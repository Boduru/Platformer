#ifndef GAME_H
#define GAME_H

class ControlHandler;
class State;

class Game
{
public:
	//Constructors/Destructors
	Game(unsigned short width, unsigned short height, std::string name);
	virtual ~Game();

	//Accessors
	float getDeltaTime();

	//Functions
	void resizeWindow(const float width, const float height);
	void toggleFullScreen();
	void changeWindowSize(float width, float height);
	void endGame();

	void configureGame();

	void checkWindowEvents();
	void updateEvents();
	void updateWindowEvents(sf::Event& event);
	void updateKeyboardEvents();
	void updateMouseEvents();
	void updateMousePosition();
	void manageStates();
	void manageMainMenuState();
	void manageSettingsState();
	void manageLevelChooserState();
	void manageGameState();
	void manageNetworkingState();
	void managePauseState();
	void update();

	void draw();
	void run();

private:
	//Objects
	sf::RenderWindow* window;
	sf::VideoMode desktop;
	sf::Clock clock;

	ControlHandler controller;
	State* state;
	PauseInternState* pauseState;

	//Keyboard
	std::map<std::string, sf::Keyboard::Key> pressed;
	std::map<std::string, sf::Keyboard::Key> released;
	std::map<std::string, sf::Keyboard::Key> tapped;
	
	//Mouse
	sf::Vector2i mousePosView;
	sf::Vector2f mousePosWindow;
	std::map<std::string, sf::Mouse::Button> clicked;
	std::map<std::string, sf::Mouse::Button> unclicked;
	std::map<std::string, sf::Mouse::Button> oneHitClicked;

	//Window based preferences
	std::string name;
	float deltaTime;
	int frameRateLimit;

	sf::Vector2f minSize;
	sf::Vector2f mediumSize;
	sf::Vector2f maxSize;

	//Pause
	bool paused;
};

#endif // !GAME_H