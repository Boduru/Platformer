#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

class Camera;

class CameraFollower : public Camera
{
private:
	//Variables
	float lerpDistance;
	float minDistance;

public:
	//Constructors/Destructors
	CameraFollower();
	CameraFollower(sf::Vector2f position, sf::Vector2f size);
	virtual ~CameraFollower();

	//Functions
	void update(sf::RenderWindow& window, Entity& follow, const float deltatime, const bool smooth = true);
};

#endif // !CAMERAFOLLOWER_H