#include "stdafx.h"

//Constructors/Destructors
CameraFollower::CameraFollower() : CameraFollower(sf::Vector2f(0, 0), sf::Vector2f(0, 0))
{
}

CameraFollower::CameraFollower(sf::Vector2f position, sf::Vector2f size)
	: Camera(position, size),
	lerpDistance(0.50f), minDistance(1.f)
{
}

CameraFollower::~CameraFollower()
{
}

//Functions
void CameraFollower::update(sf::RenderWindow& window, Entity& follow, const float deltatime, const bool smooth)
{
    float x = follow.getCenter().x;
    float y = follow.getCenter().y;

    if (smooth)
    {
        if (sqrtf(powf(this->prevPosition.x - x, 2) + powf(this->prevPosition.y - y, 2)) > this->minDistance)
        {
            x = (1 - deltatime) * this->getCenter().x + deltatime * x + follow.getSide() * this->lerpDistance + minDistance * follow.getSide();
            y = (1 - deltatime) * this->getCenter().y + deltatime * y;// -this->follow->getSide() * this->lerpDistance;
        }
    }

    this->view.setCenter(x, y);
    window.setView(this->view);
    this->prevPosition = this->view.getCenter();
}