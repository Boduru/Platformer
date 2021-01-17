#ifndef CAMERA_H
#define CAMERA_H

class Entity;

class Camera : public Entity
{
protected:
	//Variables
	sf::View view;

public:
	//Constructors/Destructors
	Camera();
	Camera(sf::Vector2f position, sf::Vector2f size);
	virtual ~Camera();

	//Accessors
	sf::View& getView();
	const sf::Vector2f getCenter() const;
	const sf::Vector2f getTopLeft() const;
	const sf::Vector2f getTopRight() const;
	const sf::Vector2f getBottomLeft() const;
	const sf::Vector2f getBottomRight() const;
	const float getTop() const;
	const float getBottom() const;
	const float getRight() const;
	const float getLeft() const;

	//Modifiers
	void setCenter(sf::Vector2f position);

	//Functions
	void restretch(const float x, const float y);
	//void setFollow(Entity* entity);
	void update(sf::RenderWindow& window, const sf::Vector2f position);
};

#endif // !CAMERA_H