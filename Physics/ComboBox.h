#ifndef COMBOBOX_H
#define COMBOBOX_H

class Button;
class Label;

class ComboBox
{
private:
	//Variables
	std::string name;

	sf::Vector2f initPos;
	sf::Vector2f posStart;
	sf::Vector2f posEnd;

	Button leftArrow;
	Button rightArrow;

	Label label;
	
	std::vector<std::string> texts;

	int currentIndex;

public:
	//Constructors/Destructors
	ComboBox();
	ComboBox(const std::string& name, const sf::Vector2f posStart, const sf::Vector2f posEnd, const std::string pathArrowSheet, const std::vector<std::string> texts);
	virtual ~ComboBox();

	//Modifiers
	void setPosition(const sf::Vector2f& position);
	void setCurrentIndex(int index);

	//Accessors
	const sf::Vector2f getInitPos() const;
	const std::string getName() const;
	const std::string getCurrentLabel() const;
	const int& getCurrentIndex() const;
	
	//Functions
	void setupArrows(const sf::Vector2f posStart, const sf::Vector2f posEnd, const std::string pathArrowSheet);

	void update(const float& deltatime, std::map<std::string, sf::Mouse::Button> clicked, std::map<std::string, sf::Mouse::Button> uncliked, sf::Vector2i mouse_pos_view, sf::Vector2f mouse_pos_window);
	void draw(sf::RenderWindow* window);
};

#endif // !COMBOBOX_H