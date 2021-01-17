#ifndef TEXTINPUT_H
#define TEXTINPUT_H

class TextInput
{
private:
	//Variables
	sf::Vector2f initPos;

	std::string name;

	std::string helpText;
	std::string content;

	sf::Vector2f initTextPos;
	sf::Vector2f labelOffset;
	sf::Vector2f barOffset;

	Button field;
	Label textLabel;
	Label helpLabel;

	sf::Texture* barTexture;
	sf::Sprite* barSprite;

	bool isActive;
	float totalTime;
	float currentTime;
	int maxLenght;

	//Functions
	std::string mapToString(std::map<std::string, sf::Keyboard::Key> tapped);

public:
	//Constructors/Destructors
	TextInput(const std::string& name, const sf::Vector2f& position, const std::string& field_texture, const std::string& bar_texture, const sf::Vector2f& label_pos, const sf::Vector2f& bar_pos, const std::string& help_text);
	virtual ~TextInput();

	//Modifiers
	void setPosition(const sf::Vector2f& position);

	//Accessors
	const sf::Vector2f getInitPos() const;
	const std::string getName() const;
	const std::string getContent() const;

	//Functions
	void addLetter(const std::string& text);
	void removeLetter();

	void update(const float& deltatime, std::map<std::string, sf::Keyboard::Key> tapped, std::map<std::string, sf::Mouse::Button> clicked, std::map<std::string, sf::Mouse::Button> uncliked, sf::Vector2i mouse_pos_view, sf::Vector2f mouse_pos_window);
	void draw(sf::RenderWindow* window);
};

#endif // TEXTINPUT_H