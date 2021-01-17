#include "stdafx.h"

//Constructors/Destructors
Camera::Camera() : Camera(sf::Vector2f(0, 0), sf::Vector2f(0, 0))
{
}

Camera::Camera(sf::Vector2f position, sf::Vector2f size)
	: Entity(position, size)
{
    this->view = sf::View(position, size);
}

Camera::~Camera()
{

}

sf::View& Camera::getView()
{
    return this->view;
}

//Accessors
const sf::Vector2f Camera::getCenter() const
{
    return this->view.getCenter();
}

const sf::Vector2f Camera::getTopLeft() const
{
    sf::Vector2f pos = this->view.getCenter();
    return sf::Vector2f(pos.x - this->size.x / 2, pos.y - this->size.y / 2);
}

const sf::Vector2f Camera::getTopRight() const
{
    sf::Vector2f pos = this->view.getCenter();
    return sf::Vector2f(pos.x + this->size.x / 2, pos.y - this->size.y / 2);
}

const sf::Vector2f Camera::getBottomLeft() const
{
    sf::Vector2f pos = this->view.getCenter();
    return sf::Vector2f(pos.x - this->size.x / 2, pos.y + this->size.y / 2);
}

const sf::Vector2f Camera::getBottomRight() const
{
    sf::Vector2f pos = this->view.getCenter();
    return sf::Vector2f(pos.x + this->size.x / 2, pos.y + this->size.y / 2);
}

const float Camera::getTop() const
{
    sf::Vector2f pos = this->view.getCenter();
    return pos.y - this->size.y / 2;
}

const float Camera::getBottom() const
{
    sf::Vector2f pos = this->view.getCenter();
    return pos.y + this->size.y / 2;
}

const float Camera::getRight() const
{
    sf::Vector2f pos = this->view.getCenter();
    return pos.x + this->size.x / 2;
}

const float Camera::getLeft() const
{
    sf::Vector2f pos = this->view.getCenter();
    return pos.x - this->size.x / 2;
}

//Modifiers
void Camera::setCenter(sf::Vector2f position)
{
    this->view.setCenter(position);
}

//Functions
void Camera::restretch(const float x, const float y)
{
    float aspectRatio = x / y;
    this->view.setSize(float(this->size.y) * aspectRatio, float(this->size.y));
    this->setSize(sf::Vector2f(float(this->size.y) * aspectRatio, float(this->size.y)));
}

void Camera::update(sf::RenderWindow& window, const sf::Vector2f position)
{
    this->view.setCenter(position);
    window.setView(this->view);
    this->prevPosition = this->view.getCenter();
}