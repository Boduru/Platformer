#ifndef DROPBOX_H
#define DROPBOX_H

class Button;

class DropBox
{
private:
	//Variables
	sf::Vector2f initPos;
	sf::Vector2f position;

	std::vector<Button> listbox;

	Button selectedItem;

	bool isSpan;

public:
	//Constructors/Destructors
	DropBox(const sf::Vector2f position, const std::vector<Button> listbox);
	virtual ~DropBox();

	//Modifiers
	void setPosition(const sf::Vector2f& position);

	//Accessors
	const sf::Vector2f getInitPos() const;
	const std::vector<Button>& getListbox() const;
	const Button& getSelectedItem() const;

	//Functions
	void init();
	void setDefault(int index);
	void update(const float& deltatime, std::map<std::string, sf::Mouse::Button> clicked, std::map<std::string, sf::Mouse::Button> uncliked, sf::Vector2i mouse_pos_view, sf::Vector2f mouse_pos_window);
	void draw(sf::RenderWindow* window);
};


#endif // !DROPBOX_H
