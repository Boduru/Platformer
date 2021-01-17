#ifndef LABEL_H
#define LABEL_H

class Label
{
private:
	//Variables
	sf::Vector2f initPos;

	sf::Text* text;
	sf::Font* font;

	int characterSize;

	std::string content;

public:
	//Constructors/Destructors
	Label(const sf::Vector2f& position, const std::string& content, const std::string& font, const int& characterSize);
	virtual ~Label();

	//Setters
	void setOrigin();
	void setPosition(const sf::Vector2f& position);
	void setContent(const std::string& content);
	void setCharacterSize(const int& size);
	void setTextTransparency(const int& amount);
	void setTextStyle(const sf::Text::Style& style);

	//Accessors
	const sf::FloatRect getGlobalBounds() const;
	const sf::Vector2f getPosition() const;
	const sf::Vector2f getInitPos() const;
	const std::string getContent() const;
	const int getCharacterSize() const;
	const sf::Color getTextColor() const;

	//Functions
	void draw(sf::RenderWindow* window);

};

#endif // !LABEL_H

