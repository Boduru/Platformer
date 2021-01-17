#pragma once

#include <map>

class ControlHandler
{
private:
	//Variables
	std::map<std::string, sf::Keyboard::Key> controls;
	std::map<std::string, sf::Mouse::Button> buttons;

public:
	//Constructors/Destructors
	ControlHandler();

	//Functions
	void initContols();

	std::map<std::string, sf::Keyboard::Key> getInputs(sf::Event& event);
	std::map<std::string, sf::Keyboard::Key> getInputsPressed();
	std::map<std::string, sf::Mouse::Button> getButtons(sf::Event& event);
	std::map<std::string, sf::Mouse::Button> getButtonsPressed();
};