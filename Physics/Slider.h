#ifndef SLIDER_H
#define SLIDER_H

class Label;

class Slider
{
private:
	//Variables
	std::string name;

	sf::Texture* textureSlider;
	sf::Texture* texturePin;

	sf::Sprite* baseSprite;
	sf::Sprite* topSprite;
	sf::Sprite* pinSprite;

	Label label;

	sf::Vector2f initPos;
	sf::Vector2f position;

	float start;
	float stop;
	float step;

	float percentage;

public:
	//Constructors/Destructors
	Slider(const std::string& name, const sf::Vector2f& position, const std::string& path_slider, const std::string& path_pin, const float& start, const float& stop, const float& step, const float& default_value);
	virtual ~Slider();

	//Modifiers
	void setPosition(const sf::Vector2f& position);

	//Accessors
	const sf::Vector2f getInitPos() const;
	const std::string getName() const;
	const float getNumber() const;

	//Functions
	bool hasOverlap(sf::Vector2i position);
	void setPercentage(const float& percentage);
	void setDefault(const float& value);

	void update(const float& deltatime, std::map<std::string, sf::Mouse::Button> clicked,
		std::map<std::string, sf::Mouse::Button> uncliked,
		sf::Vector2i mouse_pos_view,
		sf::Vector2f mouse_pos_window);
	void draw(sf::RenderWindow* window);

};

#endif // !SLIDER_H