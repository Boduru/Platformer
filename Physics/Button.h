#ifndef BUTTON_H
#define BUTTON_H

class Button
{
private:
	//Variables
	sf::Vector2f initPos;

	sf::Texture* texture;
	sf::Sprite* sprite;
	sf::Vector2f size;

	Animator animator;

	std::string name;

	bool isClicked;
	bool isHover;
	bool isReleased;

	float totalTime;
	float currentTime;

public:
	//Constructors/Destructors
	Button();
	Button(const std::string name, const float x, const float y, const std::string path, const sf::Vector2u imOffset, const bool& flip=false);
	virtual ~Button();

	//Setters
	void setPosition(sf::Vector2f position);
	void setScale(const float& factor);

	//Accessors
	const sf::Vector2f getInitPos() const;
	const sf::FloatRect getGlobalBounds() const;
	const std::string getButtonName() const;

	const bool isButtonClicked() const;
	const bool isButtonHover() const;
	const bool isButtonReleased() const;

	//Functions
	void autoconfigure();
	void configureAnimation(std::string name, unsigned start_x, unsigned end_x, unsigned start_y, unsigned end_y, float switch_time);
	bool hasOverlap(sf::Vector2i position);

	void update(const float& deltatime, std::map<std::string, sf::Mouse::Button> clicked, 
		std::map<std::string, sf::Mouse::Button> uncliked, 
		sf::Vector2i mouse_pos_view, 
		sf::Vector2f mouse_pos_window, const bool& flip=false);
	void draw(sf::RenderWindow* window);

	//Operators
	void operator=(const Button& button);
};

#endif // !BUTTON_H